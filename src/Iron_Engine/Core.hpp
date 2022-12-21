#pragma once

//SDL2
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_audio.h>
#include <SDL_image.h>
//MiniAudio
#include <Iron_Engine/vendor/miniaudio/miniaudio.h>

#define CHANNELS    2               /* Setup Stereo Audio. */
#define SAMPLE_RATE 48000
//Dear ImGui
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_sdlrenderer.h>

#include <iostream>
#include <assert.h>

//LOGGER
#ifndef DISTRIBUTION_BUILD
#define TRACE(x) printf("LOG: %s\n", x)
#define TRACE_VAR_F(x) printf("LOG: %f\n", x)
#define TRACE_VAR_I(x) printf("LOG: %i\n", x)
#define TRACE_VAR_UI(x) printf("LOG: %ui\n", x)
#define TRACE_VAR_U(x) printf("LOG: %u\n", x)
#define ERROR(x) printf("ERROR: %s\n", x)
#else
#define TRACE(x)
#define TRACE_VAR_F(x)
#define TRACE_VAR_I(x)
#define TRACE_VAR_UI(x)
#define TRACE_VAR_U(x)
#define TRACE_VAR(x)
#define ERROR(x)
#endif // !DISTRIBUTION_BUILD

#include <Iron_Engine/iniwrap.h>

//WINDOW VARIABLES
typedef struct WinConfig
{
public:
	void loadFromINI(std::string_view f)
	{
		ini_t* ini;
		iniwrap::loadINI(ini, f.data());
		height = iniwrap::readValue<int>(ini, "WinConfig", "height");
		width = iniwrap::readValue<int>(ini, "WinConfig", "width");
		vsync = iniwrap::readValue<bool>(ini, "WinConfig", "vsync");
		fpsCap = iniwrap::readValue<int>(ini, "WinConfig", "fpsCap");
	}

	void writeToINI(std::string_view f)
	{
		ini_t* ini;
		iniwrap::loadINI(ini, f.data());
		iniwrap::writeValue<int>(ini, f.data(), "WinConfig", "height", height);
		iniwrap::writeValue<int>(ini, f.data(), "WinConfig", "width", width);
		iniwrap::writeValue<bool>(ini, f.data(), "WinConfig", "vsync", vsync);
		iniwrap::writeValue<int>(ini, f.data(), "WinConfig", "fpsCap", fpsCap);
	}

	void CreateWin(SDL_Window*& win)
	{
		win = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	}

	void UpdateVsync(SDL_Renderer*& renderer)
	{
		if (SDL_RenderSetVSync(renderer, vsync) < 0)
		{
			TRACE("Unable to set VSync!");
			ERROR(SDL_GetError());
		}
	}

	void UpdateWinWH(SDL_Window*& win)
	{
		SDL_SetWindowSize(win, width, height);
	}

	void UpdateWinTitle(SDL_Window*& win)
	{
		SDL_SetWindowTitle(win, title.c_str());
	}
public:
	int width = 640, height = 640;
	std::string title = "IRON";
	bool vsync = true;
	int fpsCap = 144;
public:
	float ticksPerFrame() { return 1000 / fpsCap; }
private:
}WinConfig;

//TODO:  Implement a new audio library/framework

namespace IronGL
{
	static WinConfig m_WindowConfiguration;
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

	static void Init_SDL2(WinConfig config)
	{
		m_WindowConfiguration = config;
		uint32_t flags = SDL_INIT_VIDEO;
		if (SDL_Init(flags) < 0)
		{
			ERROR("SDL could not initialize! SDL_Error:");
			ERROR(SDL_GetError());
			exit(-1);
		}

		m_WindowConfiguration.CreateWin(m_Window);

		if (!m_Window)
		{
			ERROR("Window could not be created!\nSDL_Error: ");
			ERROR(SDL_GetError());

			exit(-1);
		}

		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (!m_Renderer)
		{
			ERROR("Renderer could not be created!\nSDL Error: ");
			ERROR(SDL_GetError());
			exit(-1);
		}
		m_WindowConfiguration.UpdateVsync(m_Renderer);

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			ERROR("SDL_image could not initialize! SDL_image Error:");
			ERROR(IMG_GetError());

			exit(-1);
		}

		m_ScreenSurface = SDL_GetWindowSurface(m_Window);
	}

	static void Init_Ex()
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