#pragma once

#include "Iron_Engine/Entity.hpp"
#include "Iron_Engine/Components/Sprite.hpp"
#include "Iron_Engine/Math/Mathf.hpp"
#include "Iron_Engine/Math/Random.hpp"
#include "Iron_Engine/Utils/Input.hpp"

class Platform : public Entity
{
public:
	Platform()
		:spr("res\\images\\platform.png"), velocity(0.0, 0.0),
		collider({ 0.0, 0.0 })
	{
		collider = Collider(spr.spr_data.clip);

		spr.SetGraphicSize(0.5);
		spr.ScreenCenter();
		spr.transform.position.y += 277;
		collider.position = spr.transform.position;
	}

	~Platform()
	{
		spr.~Sprite();
	}

	Vec2 velocity;
	void Update(const float& delta, Input& input)
	{
		collider.position = spr.transform.position;//YOU NEED TO UPDATE THE POSITION

		velocity.x = input.getAxis(Axis::HORIZONTAL);

		spr.transform.position += velocity * delta * 300;

		Mathf::clamp(spr.transform.position.x, 0, WINDOW_WIDTH - spr.spr_data.clip.x);

		Mathf::lerp(spr.transform.z_rotation, velocity.x * 15, delta * 3.5);
	}

	void Render()
	{
		spr.Render();
	}
public:
	Collider collider;
	Sprite spr;
};