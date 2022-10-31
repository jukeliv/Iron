#pragma once

//IRON
#include "Iron_Engine/Core.hpp"
//GRAPHICS
#include "Iron_Engine/Components/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Components/AudioClip.hpp"
//INPUT
#include "Iron_Engine/Utils/Input.hpp"
//GOLDEN LIBRARY
#include "Iron_Engine/Math/CollisionDetector.hpp"

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
		Text.transform.position.y += 150;

		music.Play(true);
		music.SetVolume(0.85);
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
	AudioClip music;

	Icon icon;
	Sprite Text;
};