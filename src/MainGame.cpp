#pragma once
#pragma once

//IRON
#include "Iron_Engine/Game.hpp"
//GRAPHICS
#include "Iron_Engine/Components/Sprite.hpp"
//AUDIO
#include "Iron_Engine/Components/AudioClip.hpp"
//GOLDEN LIBRARY
#include "Iron_Engine/Golden/CollisionDetector.hpp"

#include "Platform.cpp"
#include "Box.cpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
		:music("res\\music\\FutureWave.wav", AudioData::IRON_MUSIC),
		background("res\\images\\background.png"),
		gameOverScreen("res\\images\\game_over.png")
	{
		music.Play(true);
		music.SetVolume(0.75);
		
	}

	//When the program is shuting down
	~MainGame()
	{
		player.~Platform();
		music.~AudioClip();
		food.~Box();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		game_over = timer < 1 || score < 0;

		if (game_over)
			return;

		if (Golden::CollisionDetector::DetectCollision(food.collider, player.collider))
		{
			food.Reset();
			score++;
		}
		else if (food.spr.transform.position.y > WINDOW_HEIGHT + food.spr.data.bounds.x)
		{
			food.Reset(true);
			score--;
		}

		timer -= time.delta;

		player.Update(time.delta, input);

		food.Update(time.delta);
	}

	//Process SDL2 Events (Extra input related code...)
	void ProcessEvents(const SDL_Event& e)
	{
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

		uint32_t time = (int)std::floor(timer);

		ImGui::Text("Score: %u", score < 0 ? 0 : score);
		ImGui::Text("Time Left: %i", time);
		ImGui::End();
	}

public:
	AudioClip music;

	uint16_t score = 0;
	float timer = 60;

	Platform player;
	Sprite background;
	Sprite gameOverScreen;
	Box food;
private:
	bool game_over;
};