#pragma once

#include "Iron_Engine/Entity.hpp"
#include "Iron_Engine/Components/Sprite.hpp"
#include "Iron_Engine/Math/Mathf.hpp"
#include "Iron_Engine/Math/Random.hpp"
#include "Iron_Engine/Utils/Input.hpp"

class Box : public Entity
{
public: 
	Box()
		:spr("res\\images\\Box.png"),
		score_sfx("res\\sounds\\score.wav"), fail_sfx("res\\sounds\\fail.wav"),
		collider({0, 0})
	{
		collider = Collider(spr.data.clip * 0.95);
		spr.SetGraphicSize(0.65);
		spr.ScreenCenter();
		spr.transform.position.y = -Random::random_value(spr.data.clip.x * 1.5, spr.data.clip.x * 2.5);
		spr.transform.position.x = WINDOW_WIDTH / 2;
	}

	~Box()
	{
		spr.~Sprite();
		score_sfx.~AudioClip();
		fail_sfx.~AudioClip();
	}

	void Update(const float& delta)
	{
		collider.position = spr.transform.position;//YOU NEED TO UPDATE THE POSITION

		spr.transform.position.y += 400 * delta;
		spr.transform.z_rotation += 450 * delta;
	}
	
	void Reset(bool failure = false)
	{
		spr.ScreenCenter();
		spr.transform.position.y = -Random::random_value(spr.data.clip.x, spr.data.clip.x * 2.5);
		spr.transform.position.x = Random::random_value(spr.data.clip.x, WINDOW_WIDTH - spr.data.clip.x);

		if (!failure) {
			score_sfx.SetVolume(Random::random_value(0.75, 1.0));
			score_sfx.Play(false);
		}
		else
			fail_sfx.Play(false);
	}

	void Render()
	{
		spr.Render();
	}
public:
	Collider collider;
	AudioClip score_sfx;
	AudioClip fail_sfx;
	Sprite spr;
};