#pragma once

#include "Iron_Engine/Core.hpp"
#include "Iron_Engine/Game.hpp"
#include "Iron_Engine/Utils/Timer.hpp"

#include <future>

class Application
{
public:

	Application()
	{
	}

	void Init()
	{
		IronGL::Init();

		SDL_UpdateWindowSurface(IronGL::m_Window);
	}

	template <typename G>
	void SetCurrentGame()
	{
		game.release();
		game.reset();
		game = std::make_unique<G>();
	}

	void Run()
	{
		Timer fps_timer;
		Timer cap_timer;
		
		SDL_Event e;
		bool quit = false;

		while (!quit)
		{
			fps_timer.start_timer();

			game->Update();

			while (SDL_PollEvent(&e) != 0)
			{
				quit = e.type == SDL_QUIT;

				if(e.key.keysym.sym == SDLK_r)
					SetCurrentGame<MainGame>();

				game->ProcessEvents(e);
				ImGui_ImplSDL2_ProcessEvent(&e);
			}

			SDL_SetRenderDrawColor(IronGL::m_Renderer, 171, 0x0, 0x0, 0x0);

			game->Render();

			ImGui_ImplSDLRenderer_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			game->RenderUI();

			ImGui::Render();

			ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
			SDL_RenderPresent(IronGL::m_Renderer);
			
			SDL_RenderClear(IronGL::m_Renderer);

			Uint32 cap = cap_timer.elapsed_time();
			if (cap < TICKS_PER_FRAME)
			{
				SDL_Delay(TICKS_PER_FRAME - cap);
			}

			fps_timer.end_timer();

			game->delta_time = (double)fps_timer.elapsed_time() / 1000;
		}

		game->~Game();

		IronGL::Shutdown();

		exit(0);
	}
private:
	std::unique_ptr<Game> game;
};