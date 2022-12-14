#pragma once

#include <Iron_Engine\Core.hpp>
#include <string_view>

typedef struct AudioConfig
{
public:
	AudioConfig(bool _loop)
		:loop(_loop){}
public:
	bool loop = false;
}AudioConfig;

class AudioClip
{
public:
	AudioClip(std::string_view path)
	{
		ma_result result = ma_sound_init_from_file(&IronGL::g_Engine, path.data(), 0, NULL, NULL, &g_Sound);
		if (result != MA_SUCCESS) {
			printf("Failed to initialize sound.");
			exit(-1);
		}
	}

	inline void Play(AudioConfig* configuration = NULL)
	{
		ma_sound_set_looping(&g_Sound, configuration->loop);

		ma_sound_start(&g_Sound);
	}

	//The volume goes from 0.0 to 1.0
	inline void SetVolume(double v)
	{
		float volume = powf(v, 2);

		ma_sound_set_volume(&g_Sound, volume);
	}

	~AudioClip()
	{
		ma_sound_uninit(&g_Sound);
	}
private:
	ma_sound g_Sound;
};