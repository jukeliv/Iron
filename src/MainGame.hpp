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

		width = icon.spr.spr_data.w;
		height = icon.spr.spr_data.h;
	}

	//When the program is shuting down
	~MainGame()
	{
		icon.~Icon();
		cursor.~Cursor();
		music.~AudioClip();
	}

	int width, height;

	double newW, newH;

	double w, h;

	//Every Frame ( Manage Logic )
	void Update()
	{
		icon.Update(delta_time);
		cursor.Update();
		if (Golden::CollisionDetector::bounding_sqr(icon.spr, cursor.spr))
		{
			newW = width * 1.45;
			newH = height * 1.45;
		}
		else
		{
			newW = width;
			newH = height;
		}

		Mathf::lerp(w, newW, 0.65);
		Mathf::lerp(h, newH, 0.65);

		icon.spr.SetGraphicSize(w, h);

		icon.spr.ScreenCenter();
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