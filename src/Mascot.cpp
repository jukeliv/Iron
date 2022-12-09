#pragma once

#include <Iron_Engine/Engine.hpp>

class Mascot : GameObject
{
public:
	Mascot()
		:sprite("res/images/slime.png"), collider(Transform(),Golden::ColliderType::SquareCollider),
		vel(0)
	{
		animator = std::make_unique<Animator>(sprite);
		sprite.transform.scale = glm::vec2(4);
		sprite.ScreenCenter();

		sprite.transform.position.x = 0;

		animator->AddByRects("idle", { {0, 0, 21, 21}, {0, 21, 21, 21}, {21, 0, 21, 21}, {0, 21, 21, 21} }, 3);

		animator->PlayAnim("idle");
	}

	void Update(Input& input, const Time& time)
	{
		animator->step(time);
		collider.step(sprite.transform.position, glm::vec2(24));

		vel.y = input.keys[SDLK_q]?-1:1;

		sprite.transform.position += Golden::Ziffy::cal_velocity(vel, 30, time.delta);
	}

	void Render()
	{
		sprite.Render();
	}

	~Mascot()
	{
		animator.release();
		delete animator.get();
	}

public:
	std::unique_ptr<Animator> animator;
	Sprite sprite;

	Golden::Collider collider;
	glm::vec2 vel;
};