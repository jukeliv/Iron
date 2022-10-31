#pragma once

//IRON
#include "Iron_Engine/Core.hpp"
//GRAPHICS
#include "Iron_Engine/Utils/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Utils/AudioClip.hpp"
//INPUT
#include "Iron_Engine/Input.hpp"

#include "Icon.hpp"

class Game
{
public:
	//First frame after initializing SDL 2
	Game()
		:Text("res\\images\\text.png"),
		music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC)
	{
		Text.SetGraphicSize(1.5);
		Text.ScreenCenter();

		Text.transform.y += 150;

		music.Play(true);
	}

	//When the program is shuting down
	~Game()
	{
		icon.~Icon();
		Text.~Sprite();

		music.~AudioClip();
	}

	//Every Frame ( Manage Logic )
	float f = 0;
	void Update()
	{
		f += (float)1 / 60;
		music.SetVolume(sin(f) / 2.0 + 0.65);
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
	AudioClip music;

	Icon icon;
	Sprite Text;
};