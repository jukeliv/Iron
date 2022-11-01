#pragma once
#pragma once

//IRON
#include "Iron_Engine/Game.hpp"
//GRAPHICS
#include "Iron_Engine/Components/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Components/AudioClip.hpp"
//Math
#include "Iron_Engine/Math/Mathf.hpp"
//GOLDEN LIBRARY
#include "Iron_Engine/Golden/CollisionDetector.hpp"

#include "Icon.hpp"

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
		music.~AudioClip();
	}

	int width, height;

	double newW, newH;

	double w, h;

	//Every Frame ( Manage Logic )
	void Update()
	{
		icon.Update(delta_time, input);
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		icon.Render();
	}

	void RenderUI()
	{
		ImGui::Begin("example");

		ImGui::Text("you cant interact with the ui lol");

		ImGui::End();
	}
public:
	AudioClip music;

	Icon icon;
};