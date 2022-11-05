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
#include "Iron_Engine/Math/Random.hpp"
//GOLDEN LIBRARY
#include "Iron_Engine/Golden/CollisionDetector.hpp"

#include "Platform.cpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
		:music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC),
		background("res\\images\\background.png"),
		gameOverScreen("res\\images\\game_over.png"),
		LOL("res\\images\\box.png")
	{
		background.ScreenCenter();
		
		music.Play(true);
		music.SetVolume(0.75);
		
	}

	//When the program is shuting down
	~MainGame()
	{
		player.~Platform();
		music.~AudioClip();
		//food.~Box();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		if (timer < 1  || score < 0)
		{
			game_over = true;
			return;
		}

		//food.Update(delta_time);

		/*Scoring
		if (Golden::CollisionDetector::bounding_sqr(food.spr, player.spr, 1.05))
		{
			//food.Reset();
			score++;
		}

		if (food.spr.transform.position.y > WINDOW_HEIGHT + food.spr.spr_data.h)
		{
			//food.Reset();
			score--;
		}*/

		timer -= delta_time;
		player.Update(delta_time, input);
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		if (game_over)
		{
			gameOverScreen.Render();
			return;
		}
		background.Render();

		player.Render();
		//food.Render();
		LOL.Render();
	}

	void RenderUI()
	{
		ImGui::Begin(" -- Example UI -- ");

		uint32_t time = (int)std::floor(timer);

		ImGui::Text("Score: %i\nTime Left: %i", score < 0 ? 0 : score, time);

		ImGui::End();
	}

public:
	AudioClip music;

	int score = 0;
	float timer = 30;

	Platform player;
	Sprite background;
	Sprite gameOverScreen;
	Sprite LOL;
private:
	bool game_over;
};