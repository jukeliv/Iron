#pragma once

#include <Iron_Engine/Engine.hpp>

class Platform : public Entity
{
public:
	Platform()
		:spr("res\\images\\platform.png"), velocity(0.0),
		collider({}, ColliderType::SquareCollider)
	{
		spr.transform.scale = glm::vec2(0.5);
		spr.ScreenCenter();
		spr.transform.position.y += 277;

		collider.bounds = spr.transform;
	}

	~Platform()
	{
		spr.~Sprite();
	}

	void Update(const float& delta, Input& input)
	{
		collider.bounds = spr.transform;//YOU NEED TO UPDATE THE POSITION

		velocity.x = input.getAxis(Axis::HORIZONTAL);

		spr.transform.position += velocity * delta * 300.0f;

		Mathf::clamp(spr.transform.position.x, 0, WINDOW_WIDTH - spr.data.bounds.x);

		Mathf::lerp(spr.transform.rotation, velocity.x * 15, delta * 3.5);
	}

	void Render()
	{
		spr.Render();
	}
public:
	glm::vec2 velocity;
	Collider collider;
	Sprite spr;
};