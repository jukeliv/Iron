#include "MainGame.cpp"
#include "Iron_Engine/Utils/Timer.hpp"
/*
*				  REMEMBER
* "Game.h" is where you write all your logic
*/

int main(int argc, char* argv[]) 
{
	IronGL::Init();
	std::unique_ptr<Game> game = std::make_unique<MainGame>();

	SDL_UpdateWindowSurface(IronGL::m_Window);

	SDL_Event e; 
	uint8_t quit = 0x0;

	float start_time;

	Timer fps_timer;
	Timer cap_timer;

	while (!quit)
	{
		fps_timer.start_timer();

		game->Update();

		while (SDL_PollEvent(&e) != 0x0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 0xFF;
				break;
			case SDL_KEYDOWN:
				game->input.keys[e.key.keysym.sym] = 0xFF;
				break;
			case SDL_KEYUP:
				game->input.keys[e.key.keysym.sym] = 0x0;
				break;
			}
		}

		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		game->RenderUI();

		ImGui::Render();
		SDL_SetRenderDrawColor(IronGL::m_Renderer, 171, 0xFF, 3, 0xFF);

		SDL_RenderClear(IronGL::m_Renderer);

		game->Render();

		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		SDL_RenderPresent(IronGL::m_Renderer);


		fps_timer.end_timer();

		float cap = cap_timer.elapsed_time();
		if (cap < TICKS_PER_FRAME)
		{
			SDL_Delay(TICKS_PER_FRAME - cap);
		}

		game->delta_time = (double)fps_timer.elapsed_time() / 1000;
	}

	game->~Game();

	IronGL::Shutdown();

	exit(0x0);
}