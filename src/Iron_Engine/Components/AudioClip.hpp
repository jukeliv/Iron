#pragma once
//TODO: ReWrite this class with another Audio Library/Framework
/*
#include <Iron_Engine\Core.hpp>

#include <string_view>

enum class AudioData { IRON_MUSIC, IRON_SFX };

typedef struct AudioConfig
{
public:
	AudioConfig(bool _loop, bool _force)
		:loop(_loop), force(_force)
	{

	}
public:
	bool loop = false;
	bool force = false;
}AudioConfig;

class AudioClip
{
public:
	AudioClip(std::string_view path, AudioData data = AudioData::IRON_SFX)
		:m_Data(data)
	{
		if (m_Data == AudioData::IRON_MUSIC) {
			m_MusicClip = Mix_LoadMUS(path.data());

			if (!m_MusicClip)
			{
				ERROR("Failed to load music!");
				ERROR(path.data());
				ERROR("SDL_MIXER ERROR: ");
				ERROR(Mix_GetError());

				exit(-1);
			}
		}
		else
		{
			m_AudioClip = Mix_LoadWAV(path.data());

			if (!m_AudioClip)
			{
				ERROR("Failed to load music!");
				ERROR(path.data());
				ERROR("SDL_MIXER ERROR: ");
				ERROR(Mix_GetError());

				exit(-1);
			}
		}
	}

	inline void Play(AudioConfig* configuration = NULL)
	{
		if (m_Data == AudioData::IRON_MUSIC)
		{
			if (Mix_PlayingMusic() == 0 || configuration->force)
			{
				Mix_PlayMusic(m_MusicClip, configuration->loop?-1:0);
			}
		}
		else
		{
			Mix_PlayChannel(-1, m_AudioClip, configuration->loop ?-1:0);
		}
	}

	//The volume goes from 0.0 to 1.0
	inline void SetVolume(double v)
	{
		uint32_t volume = std::ceil(powf(v, 2) * MIX_MAX_VOLUME);

		if (m_Data == AudioData::IRON_MUSIC)
			Mix_VolumeMusic(volume);
		else
			Mix_VolumeChunk(m_AudioClip, volume);
	}

	~AudioClip()
	{
		Mix_FreeMusic(m_MusicClip);
		m_MusicClip = nullptr;

		Mix_FreeChunk(m_AudioClip);
		m_AudioClip = nullptr;
	}
private:
	AudioData& m_Data;

	Mix_Music* m_MusicClip = nullptr;
	Mix_Chunk* m_AudioClip = nullptr;
};*/