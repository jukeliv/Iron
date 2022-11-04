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
#include "Iron_Engine/Math/Random.hpp"

#include "Platform.cpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
		:music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC),
		background("res\\images\\background.png"), food("res\\images\\box.png"),
		gameOverScreen("res\\images\\game_over.png")
	{
		food.SetGraphicSize(0.65);
		Reset(food);
		food.transform.position.x = WINDOW_WIDTH / 2;

		background.ScreenCenter();
		music.Play(true);
		music.SetVolume(0.75);
	}

	//When the program is shuting down
	~MainGame()
	{
		player.~Platform();
		music.~AudioClip();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		if (timer < 1  || score < 0)
		{
			game_over=true;
			return;
		}


		food.transform.position.y += 400 * delta_time;
		food.transform.z_rotation += 450 * delta_time;

		//Scoring
		if (Golden::CollisionDetector::bounding_sqr(food, player.spr, 1.05))
		{
			Reset(food);
			score++;
		}
		if (food.transform.position.y > WINDOW_HEIGHT + food.spr_data.h)
		{
			Reset(food);
			score--;
		}

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
		food.Render();
	}

	void RenderUI()
	{
		ImGui::Begin(" -- Example UI -- ");

		ImGui::Text("Score: %i\nTime Left: %i", score, (int)std::floor(timer));

		ImGui::End();
	}

	void Reset(Sprite& spr)
	{
		spr.ScreenCenter();
		spr.transform.position.y = -Random::random_value(spr.spr_data.w*1.5, spr.spr_data.w * 2.5);
		spr.transform.position.x = Random::random_value(spr.spr_data.w, WINDOW_WIDTH - spr.spr_data.w);

		spr.transform.position.x = std::abs(spr.transform.position.x);
	}

public:
	AudioClip music;

	int score = 0;
	float timer = 30;

	Platform player;
	Sprite food;
	Sprite background;
	Sprite gameOverScreen;
private:
	bool game_over;
};