#pragma once

#include <Iron_Engine\Core.hpp>
#include <string_view>

typedef struct AudioConfig
{
public:
	char loop = false;
	//value goes from -1 to 1
	float panning = 0.0f;
	//value goes from 0 to 1
	float volume = 1.0f;
	float pitch = 1.0f;
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

	void Play()
	{
		step();

		ma_sound_set_looping(&m_Sound, m_Config.loop);

		ma_sound_start(&m_Sound);
	}

	void step()
	{
		ma_sound_set_position(&m_Sound, m_Config.panning, 0.0f, 0.0f);

		ma_sound_set_volume(&m_Sound, powf(m_Config.volume, 2));

		ma_sound_set_pitch(&m_Sound, m_Config.pitch);
	}

	~AudioClip()
	{
		ma_sound_uninit(&m_Sound);
	}
public:
	AudioConfig m_Config;
private:
	ma_sound m_Sound;
};
