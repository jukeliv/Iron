#pragma once

#include <Iron_Engine\Core.hpp>
#include <string_view>

typedef struct AudioConfig
{
public:
	/*on enabled, performance gets better, but memory usage increase
	* if your file is large and/or its only played ones, enable this
	* if it is small and/or it's used many times, let it as it is right now
	*/
	char fast = false;
	//enables playing the song again when it ends
	char loop = false;
	//value goes from -1 to 1
	float panning = 0.0f;
	//value goes from 0 to 1
	float volume = 1.0f;
	//this affects speed too
	float pitch = 1.0f;
}AudioConfig;

class AudioClip
{
public:
	AudioClip(std::string_view path)
	{
		ma_result result = ma_sound_init_from_file(&IronGL::g_Engine, path.data(), (ma_uint32)m_Config.fast?MA_SOUND_FLAG_DECODE:MA_SOUND_FLAG_STREAM, NULL, NULL, &m_Sound);

		if (result != MA_SUCCESS) {
			ERROR("Failed to initialize sound.");
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
