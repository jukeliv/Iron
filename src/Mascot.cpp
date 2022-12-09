#pragma once

#include <Iron_Engine/Engine.hpp>

class Mascot : GameObject
{
public:
	Mascot()
		:animator("res/images/slime.png"), collider(Transform(),Golden::ColliderType::SquareCollider),
		vel(0)
	{
		animator.spr.transform.scale = glm::vec2(4);
		animator.spr.ScreenCenter();

		animator.spr.transform.position.x = 0;

		animator.AddByRects("blink", { {0, 0, 21, 21}, {0, 21, 21, 21}, {21, 0, 21, 21}, {0, 21, 21, 21} });

		animator.PlayAnim("blink");
	}

	void Update(Input& input, const Time& time)
	{
		animator.step(time);
		collider.step(animator.spr.transform.position, glm::vec2(24));

		vel.y = input.keys[SDLK_q]?-1:1;

		animator.spr.transform.position += Golden::Ziffy::cal_velocity(vel, 30, time.delta);
	}

	void Render()
	{
		animator.spr.Render();
	}

public:
	Animator animator;
	Golden::Collider collider;
	glm::vec2 vel;
};