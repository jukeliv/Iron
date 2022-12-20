#pragma once

#include <Iron_Engine/Engine.hpp>

class Application
{
public:

	Application()
	{
	}

	void Init(WinConfig config)
	{
		//IronGL::Init();
		IronGL::Init_SDL2(config);
		SDL_FillRect(IronGL::m_ScreenSurface, NULL, SDL_MapRGB(IronGL::m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(IronGL::m_Window);
		 //this is just a simple splash screen

		Transform trasnform;
		Transform trasnform2;
		Camera cam;
		Sprite spr(trasnform, "Iron/preloader.png");
		spr.data.bounds.x = config.width;
		spr.data.bounds.y = config.height;

		Sprite c(trasnform2, "Iron/preloader_logo.png");
		trasnform2.scale = glm::vec2((config.width+config.height/2)/640*1.5f);
		c.ScreenCenter();
		c.transform.position.y = config.width;

		//dont move this, or else the audio its not going to play
		IronGL::Init_Ex();

		AudioClip clip("Iron/preloader.mp3");
		clip.m_Config.fast = true;
		clip.Play();

		float elapsed = 0;
		while (elapsed <= 7) {
			fps_timer.start_timer();

			SDL_RenderClear(IronGL::m_Renderer);
			spr.Render(cam);

			if(elapsed <= 1)
				trasnform2.position.y = Matloon::slerp(trasnform2.position.y, (float)config.height / 2 - (c.data.bounds.y * trasnform2.scale.y / 2), elapsed);

			c.Render(cam);
			SDL_RenderPresent(IronGL::m_Renderer);

			fps_timer.end_timer();

			elapsed += (float)fps_timer.elapsed_time()/1000;
		}

		clip.Stop();
	}

	template <typename T>
	void SetCurrentGame()
	{
		game.release();
		game.reset();
		game = std::make_unique<T>();
	}

	SDL_Event e;
	char quit = false;
	Timer fps_timer;
	void Run()
	{
		Timer cap_timer;

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
			if (cap < IronGL::m_WindowConfiguration.ticksPerFrame())
			{
				SDL_Delay(IronGL::m_WindowConfiguration.ticksPerFrame() - cap);
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