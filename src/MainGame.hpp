#pragma once
#pragma once

//IRON
#include "Iron_Engine/Game.hpp"
//GRAPHICS
#include "Iron_Engine/Components/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Components/AudioClip.hpp"
//GOLDEN LIBRARY
#include "Iron_Engine/Math/CollisionDetector.hpp"
#include "Iron_Engine/Math/Mathf.hpp"

#include "Icon.hpp"
#include "Cursor.hpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
		:music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC)
	{

		music.Play(true);
		music.SetVolume(0.85);
	}

	//When the program is shuting down
	~MainGame()
	{
		icon.~Icon();
		cursor.~Cursor();
		music.~AudioClip();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		icon.Update();
		cursor.Update();
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		icon.Render();
		cursor.Render();
	}
public:
	AudioClip music;

	Icon icon;
	Cursor cursor;
};