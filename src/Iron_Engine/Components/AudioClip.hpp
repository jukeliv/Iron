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
		ma_result result = ma_sound_init_from_file(&IronGL::g_Engine, path.data(), 0, NULL, NULL, &m_Sound);
		if (result != MA_SUCCESS) {
			printf("Failed to initialize sound.");
			exit(-1);
		}
	}

	void Play(AudioConfig* configuration = NULL)
	{
		ma_sound_set_looping(&m_Sound, configuration->loop);

		ma_sound_start(&m_Sound);
	}

	//The volume goes from 0.0 to 1.0
	void SetVolume(double v)
	{
		float volume = powf(v, 2);

		ma_sound_set_volume(&m_Sound, volume);
	}

	~AudioClip()
	{
		ma_sound_uninit(&m_Sound);
	}
private:
	ma_sound m_Sound;
};
