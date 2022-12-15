#pragma once

#include <Iron_Engine/Engine.hpp>

class Box : GameObject
{
public:
	Box(float x)
		:sprite(transform,"res/images/slime.png"), collider(Transform(), Golden::ColliderType::SquareCollider)
	{
		this->transform.scale = glm::vec2(4);
		Reset();
		this->transform.position.x = x;
		sprite.data.clip.w = sprite.data.clip.h = 21;
		sprite.data.clip.x = sprite.data.clip.y = 21;
	}

	void Update(const Time& time)
	{
		collider.step(sprite);

		if (sprite.culling && sprite.transform.position.x<0)
			Reset();

		this->transform.position.x-=300* time.delta;
	}

	void Reset()
	{
		this->transform.position.y = Random::random_value(0, WINDOW_HEIGHT - sprite.data.bounds.y);
		this->transform.position.x = WINDOW_WIDTH;
	}

	void Render()
	{
		sprite.Render();
	}
public:
	Sprite sprite;
	Golden::Collider collider;
};