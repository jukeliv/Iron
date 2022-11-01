#include "MainGame.hpp"

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

	double start_time;
	while (!quit)
	{
		start_time = SDL_GetTicks64();
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

		SDL_SetRenderDrawColor(IronGL::m_Renderer, 171, 0xFF, 3, 0xFF);

		SDL_RenderClear(IronGL::m_Renderer);

		game->Render();

		SDL_RenderPresent(IronGL::m_Renderer);

		game->delta_time = (double)(SDL_GetTicks64() - start_time) / 100;
	}

	game->~Game();

	IronGL::Shutdown();

	exit(0x0);
}