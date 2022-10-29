#pragma once
#include "Iron_Engine\Utils\Entity.hpp"
#include "Iron_Engine\Utils\Sprite.hpp"

class Icon : public Entity
{
public:
	Icon()
		:spr("res\\images\\icon.png")
	{
		spr.ScreenCenter();
		spr.transform.y -= 130;
	}

	~Icon()
	{
		spr.~Sprite();
	}

	void Update()
	{
		tick += (float)1 / 60;
		spr.transform.z_rotation = (double)cos(tick) * 34;
		spr.transform.y += (double)cos(tick);
	}

	void Render()
	{
		spr.Render();
	}
public:
	Sprite spr;

private:
	float tick = 0;
};