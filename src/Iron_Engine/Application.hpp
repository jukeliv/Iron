#pragma once

#include "Iron_Engine/Core.hpp"
#include "Iron_Engine/Game.hpp"
#include "Iron_Engine/Utils/Timer.hpp"

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
				switch (e.type)
				{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					game->input.keys[e.key.keysym.sym] = true;
					break;
				case SDL_KEYUP:
					game->input.keys[e.key.keysym.sym] = false;
					break;
				}
				ImGui_ImplSDL2_ProcessEvent(&e);
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