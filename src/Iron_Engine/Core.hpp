#pragma once

//SDL2
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_image.h>
//MiniAudio
#include "miniaudio.h"

#define CHANNELS    2               /* Setup Stereo Audio. */
#define SAMPLE_RATE 48000
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
#define TRACE_VAR(x) printf("LOG: %f\n", x)
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

	//START - MINIAUDIO
	static ma_engine g_Engine;
	SDL_AudioDeviceID deviceID;

	static void data_callback(void* pUserData, ma_uint8* pBuffer, int bufferSizeInBytes)
	{
		//Reading is just a matter of reading straight from the engine.
		ma_uint32 bufferSizeInFrames = (ma_uint32)bufferSizeInBytes / ma_get_bytes_per_frame(ma_format_f32, ma_engine_get_channels(&g_Engine));
		ma_engine_read_pcm_frames(&g_Engine, pBuffer, bufferSizeInFrames, NULL);
	}
	//END - MINIAUDIO

	void Init_SDL2()
	{
		uint32_t flags = SDL_INIT_VIDEO;
		if (SDL_Init(flags) < 0)
		{
			ERROR("SDL could not initialize! SDL_Error:");
			ERROR(SDL_GetError());
			exit(-1);
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

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			ERROR("SDL_image could not initialize! SDL_image Error:");
			ERROR(IMG_GetError());

			exit(-1);
		}

		m_ScreenSurface = SDL_GetWindowSurface(m_Window);
	}

	void Init_Ex()
	{
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

		//Miniaudio
		ma_result result;
		ma_engine_config engineConfig = ma_engine_config_init();

		SDL_AudioSpec desiredSpec;
		SDL_AudioSpec obtainedSpec;

		engineConfig.noDevice = MA_TRUE;      //<-- Make sure this is set so that no device is created (we'll deal with that ourselves).
		engineConfig.channels = CHANNELS;
		engineConfig.sampleRate = SAMPLE_RATE;

		result = ma_engine_init(&engineConfig, &g_Engine);
		if (result != MA_SUCCESS) {
			ERROR("Failed to initialize audio engine.");
			exit(-1);
		}

		if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0) {
			ERROR("Failed to initialize SDL sub-system.");
			exit(-1);
		}

		//MA_ZERO_OBJECT(&desiredSpec);
		desiredSpec.freq = ma_engine_get_sample_rate(&g_Engine);
		desiredSpec.format = AUDIO_F32;
		desiredSpec.channels = ma_engine_get_channels(&g_Engine);
		desiredSpec.samples = 512;
		desiredSpec.callback = data_callback;
		desiredSpec.userdata = NULL;

		deviceID = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, &obtainedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);
		if (deviceID == 0) {
			printf("Failed to open SDL audio device.");
			exit(-1);
		}

		SDL_PauseAudioDevice(deviceID, 0);
	}

	void Shutdown()
	{
		//Unitialize MiniSound
		ma_engine_uninit(&g_Engine);
		SDL_CloseAudioDevice(deviceID);
		//Destroy window
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = NULL;
		SDL_DestroyWindow(m_Window);
		m_Window = NULL;
		m_ScreenSurface = NULL;
		SDL_QuitSubSystem(SDL_INIT_AUDIO);
		SDL_Quit();
		//Unitialize ImGui
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_Quit();
	}
}