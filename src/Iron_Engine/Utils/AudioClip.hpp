#pragma once
#include "Iron_Engine\Core.hpp"
#include <string_view>

enum class AudioData { IRON_MUSIC, IRON_SFX };

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
				ERROR("Failed to load music! SDL_mixer Error:");
				ERROR(Mix_GetError());
			}
		}
		else
		{
			m_AudioClip = Mix_LoadWAV(path.data());

			if (!m_AudioClip)
			{
				ERROR("Failed to load sound effect! SDL_mixer Error:");
				ERROR(Mix_GetError());
			}
		}
	}

	void Play(bool force = false)
	{
		if (m_Data == AudioData::IRON_MUSIC)
		{
			if (Mix_PlayingMusic() == 0 || force)
			{
				Mix_PlayMusic(m_MusicClip, -1);
			}
		}
		else
		{
			Mix_PlayChannel(-1, m_AudioClip, 0);
		}
	}

	~AudioClip()
	{
		if (m_Data == AudioData::IRON_MUSIC)
		{
			Mix_FreeMusic(m_MusicClip);
			m_MusicClip = nullptr;
		}
		else
		{
			Mix_FreeChunk(m_AudioClip);
			m_AudioClip = nullptr;
		}
	}
private:
	AudioData m_Data;

	Mix_Music* m_MusicClip = nullptr;
	Mix_Chunk* m_AudioClip = nullptr;
};