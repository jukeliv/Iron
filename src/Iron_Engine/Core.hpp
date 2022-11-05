#pragma once

//SDL 2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Im Gui
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_sdl.h>
#include <ImGui\imgui_impl_sdlrenderer.h>

#include <iostream>

//WINDOW VARIABLES
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define WINDOW_TITLE "IRON: Test Project"

#define FPS_CAP 60
#define TICKS_PER_FRAME (FPS_CAP / 1000)

//LOGGER
#ifndef DISTRIBUTION_BUILD
#define TRACE(x) printf("LOG: %s\n", x)
#define TRACE_VAR(x) printf("LOG: %f\n", x)
#define ERROR(x) printf("ERROR: %s\n", x)
#else
#define TRACE(x)
#define TRACE_VAR(x)
#define ERROR(x)
#endif // !DISTRIBUTION_BUILD

namespace IronGL
{
	SDL_Window* m_Window = nullptr;
	SDL_Surface* m_ScreenSurface = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	void Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			ERROR("SDL could not initialize! SDL_Error:");
			ERROR(SDL_GetError());
			exit(SDL_Init(SDL_INIT_VIDEO));
		}

		m_Window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

		if (!m_Window)
		{
			ERROR("Window could not be created! SDL_Error: ");
			ERROR(SDL_GetError());

			exit(-1);
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_Renderer)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			exit(-1);
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		/*
		int configFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableSetMousePos | ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags = configFlags;*/


		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		if (!ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer))
		{
			ERROR("ImGui with SDLRenderer could not initialize:");
		}
		if (!ImGui_ImplSDLRenderer_Init(m_Renderer))
		{
			ERROR("ImGui could not initialize Renderer");
		}

		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			ERROR("SDL_image could not initialize! SDL_image Error:");
			ERROR(IMG_GetError());

			exit(-1);
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			ERROR("SDL_mixer could not initialize! SDL_mixer Error:");
			ERROR(Mix_GetError());
			exit(-1);
		}

		m_ScreenSurface = SDL_GetWindowSurface(m_Window);

		SDL_FillRect(m_ScreenSurface, NULL, SDL_MapRGB(m_ScreenSurface->format, 0xFF, 0xFF, 0xFF));
	}
	void Shutdown()
	{
		//Destroy window
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = NULL;
		SDL_DestroyWindow(m_Window);
		m_Window = NULL;
		SDL_Quit();

		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_Quit();
	}
}