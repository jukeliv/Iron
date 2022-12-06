#pragma once

#include <Iron_Engine/Engine.hpp>

class Box : GameObject
{
public:
	Box()
		:sprite("res/images/slime.png"), collider(Transform(), Golden::ColliderType::SquareCollider)
	{
		sprite.transform.scale = glm::vec2(4);
	}

	void Update()
	{
		collider.step(sprite);
	}

	void Render()
	{
		sprite.Render();
	}
public:
	Sprite sprite;
	Golden::Collider collider;
};