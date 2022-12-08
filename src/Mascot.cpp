#pragma once

#include <Iron_Engine/Engine.hpp>

class Mascot : GameObject
{
public:
	Mascot()
		:sprite("res/images/slime.png"), collider(Transform(),Golden::ColliderType::SquareCollider),
		vel(0)
	{
		sprite.transform.scale = glm::vec2(4);
		sprite.ScreenCenter();

		sprite.transform.position.x = 0;
		sprite.data.clip.w = sprite.data.clip.h = 21;
	}

	void Update(Input& input, const Time& time)
	{
		collider.step(sprite.transform.position, glm::vec2(24));

		vel.y = input.keys[SDLK_q]?-1:1;

		sprite.transform.position += Golden::Ziffy::cal_velocity(vel, 30, time.delta);
	}

	void Render()
	{
		sprite.Render();
	}

public:
	Sprite sprite;
	Golden::Collider collider;
	glm::vec2 vel;
};