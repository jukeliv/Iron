#pragma once

//SDL2
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Dear ImGui
#include <ImGui\imgui.h>
#include <ImGui\imgui_impl_sdl.h>
#include <ImGui\imgui_impl_sdlrenderer.h>

#include <iostream>
#include <assert.h>

//WINDOW VARIABLES
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

#define WINDOW_TITLE "IRON: Test Project"

#define ENABLE_VSYNC true

#define FPS_CAP 144
#define TICKS_PER_FRAME (1000 / FPS_CAP)

//LOGGER
#ifndef DISTRIBUTION_BUILD
#define TRACE(x) printf("LOG: %s\n", x)
#define TRACE_VAR(x) printf("LOG: %u\n", x)
#define ERROR(x) printf("ERROR: %s\n", x)
#else
#define TRACE(x)
#define TRACE_VAR(x)
#define ERROR(x)
#endif // !DISTRIBUTION_BUILD

//TODO:  Implement a new audio library/framework

namespace IronGL
{
	SDL_Window* m_Window;
	SDL_Surface* m_ScreenSurface;
	SDL_Renderer* m_Renderer;

	void Init()
	{
		unsigned int flags = SDL_INIT_VIDEO/*| SDL_INIT_AUDIO*/;
		if (SDL_Init(flags) < 0)
		{
			ERROR("SDL could not initialize! SDL_Error:");
			ERROR(SDL_GetError());
			exit(SDL_Init(flags));
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

		if (SDL_RenderSetVSync(m_Renderer, ENABLE_VSYNC) < 0)
		{
			TRACE("Unable to set VSync!");
			ERROR(SDL_GetError());
		}

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		if (!ImGui_ImplSDL2_InitForSDLRenderer(m_Window, m_Renderer) || !ImGui_ImplSDLRenderer_Init(m_Renderer))
		{
			ERROR("ImGui could not initialize Renderer");

			exit(-1);
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			ERROR("SDL_image could not initialize! SDL_image Error:");
			ERROR(IMG_GetError());

			exit(-1);
		}

		/*
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			ERROR("SDL_mixer could not initialize! SDL_mixer Error:");
			ERROR(Mix_GetError());
			exit(-1);
		}*/

		m_ScreenSurface = SDL_GetWindowSurface(m_Window);
	}

	void Shutdown()
	{
		//Destroy window
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = NULL;
		SDL_DestroyWindow(m_Window);
		m_Window = NULL;
		m_ScreenSurface = NULL;
		SDL_Quit();

		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_Quit();
	}
}