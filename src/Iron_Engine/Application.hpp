#pragma once

#include <Iron_Engine/Engine.hpp>

class Application
{
public:

	Application()
	{
	}

	void Init()
	{
		IronGL::Init();

		SDL_FillRect(IronGL::m_ScreenSurface, NULL, SDL_MapRGB(IronGL::m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(IronGL::m_Window);
	}

	template <typename T>
	void SetCurrentGame()
	{
		try {
			game.release();
			game.reset();
			game = std::make_unique<T>();

			if(game.get() == nullptr)
				throw("ERROR LOADING SCENE");
		}
		catch (const char* e)
		{
			ERROR(e);
		}
	}

	void Run()
	{
		Timer fps_timer;
		Timer cap_timer;
		
		SDL_Event e;
		char quit = false;

		Game* gm = game.get();

		while (!quit)
		{
			fps_timer.start_timer();

			game->Update();

			while (SDL_PollEvent(&e) != 0)
			{
				quit = (e.type == SDL_QUIT);

				uint32_t key = e.key.keysym.sym;

				switch (e.type)
				{
				case SDL_KEYDOWN:
					gm->input.keys[key] = true;
					break;
				case SDL_KEYUP:
					gm->input.keys[key] = false;
					break;
				}

				gm->ProcessEvents(e);
				ImGui_ImplSDL2_ProcessEvent(&e);
			}

			SDL_SetRenderDrawColor(IronGL::m_Renderer, 0x0, 0x0, 0x0, 0xFF);
			SDL_RenderClear(IronGL::m_Renderer);
			
			gm->Render();

			ImGui_ImplSDLRenderer_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			gm->RenderUI();

			ImGui::Render();

			ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
			SDL_RenderPresent(IronGL::m_Renderer);

			Uint32 cap = cap_timer.elapsed_time();
			if (cap < TICKS_PER_FRAME)
			{
				SDL_Delay(TICKS_PER_FRAME - cap);
			}

			fps_timer.end_timer();
			gm->time.step((float)fps_timer.elapsed_time() / 1000);
		}

		gm->~Game();

		IronGL::Shutdown();

		exit(0);
	}
private:
	std::unique_ptr<Game> game;
};