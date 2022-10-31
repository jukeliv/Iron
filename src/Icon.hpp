#pragma once

#include "Iron_Engine\Entity.hpp"
#include "Iron_Engine\Components\Sprite.hpp"

class Icon : public Entity
{
public:
	Icon()
		:spr("res\\images\\icon.png"),
		tick(0)
	{
		spr.SetGraphicSize(1.5);
		spr.ScreenCenter();
	}

	~Icon()
	{
		spr.~Sprite();
	}

	void Update()
	{
		tick += (double)1/60;
		spr.transform.z_rotation = (double)cos(tick) * 34;
		spr.transform.position.y += (double)cos(tick)/2;
	}

	void Render()
	{
		spr.Render();
	}
public:
	Sprite spr;

private:
	double tick;
};