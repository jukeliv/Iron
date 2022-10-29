#pragma once

//IRON
#include "Iron_Engine/Core.hpp"
//GRAPHICS
#include "Iron_Engine/Utils/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Utils/AudioClip.hpp"
//INPUT
#include "Iron_Engine/Utils/Input.hpp"

#include "Icon.hpp"

class Game
{
public:
	//First frame after initializing SDL 2
	Game()
		:Text("res\\images\\text.png"),
		music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC)
	{
		Text.transform.x = WINDOW_WIDTH / 2 - (Text.m_Width / 2);
		Text.transform.y = WINDOW_HEIGHT / 2 - (Text.m_Height / 2) + 150;

		music.Play();
	}

	//When the program is shuting down
	~Game()
	{
		icon.~Icon();
		Text.~Sprite();

		music.~AudioClip();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		icon.Update();
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		icon.Render();
		Text.Render();
	}
public:
	Input input;//ALWAYS ADD AN "Input" HERE!!!

	Icon icon;
	Sprite Text;

	AudioClip music;
};