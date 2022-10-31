#pragma once

#include "Iron_Engine\Entity.hpp"
#include "Iron_Engine\Components\Sprite.hpp"

class Cursor : public Entity
{
public:
	Cursor()
		:spr("res\\images\\cursor.png"),
		tick(0)
	{
		spr.SetGraphicSize(0.75);
		SDL_ShowCursor(SDL_DISABLE);
	}

	~Cursor()
	{
		spr.~Sprite();
	}

	int xMouse, yMouse;

	void Update()
	{
		SDL_GetGlobalMouseState(&xMouse, &yMouse);

		Mathf::lerp(spr.transform.position.x, xMouse - (WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 10), 0.5);
		Mathf::lerp(spr.transform.position.y, yMouse - spr.spr_data.h * 1.5, 0.5);
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