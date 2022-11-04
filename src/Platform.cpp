#pragma once

#include "Iron_Engine/Entity.hpp"
#include "Iron_Engine/Components/Sprite.hpp"
#include "Iron_Engine/Math/Mathf.hpp"
#include "Iron_Engine/Utils/Input.hpp"

class Platform : public Entity
{
public:
	Platform()
		:spr("res\\images\\platform.png"), velocity(0.0, 0.0)
	{
		spr.SetGraphicSize(0.5);
		spr.ScreenCenter();
		spr.transform.position.y += 277;
	}

	~Platform()
	{
		spr.~Sprite();
	}

	Vec2 velocity;
	void Update(const double& delta, Input& input)
	{
		if (input.keys[SDLK_a] || input.keys[SDLK_LEFT])
			velocity.x = -1;
		else if (input.keys[SDLK_d] || input.keys[SDLK_RIGHT])
			velocity.x = 1;
		else
			velocity.x = 0;

		spr.transform.position.x += velocity.x * 300 * delta;
		Mathf::clamp(spr.transform.position.x, 0, WINDOW_WIDTH - spr.spr_data.w);

		Mathf::lerp(spr.transform.z_rotation, velocity.x * 15, 0.1);
	}

	void Render()
	{
		spr.Render();
	}
public:
	Sprite spr;
};