#pragma once

#include <Iron_Engine/Engine.hpp>
#include "Box.cpp"

class ObstacleHandler
{
public:
	ObstacleHandler()
		:box2(WINDOW_WIDTH * 1.5f), box1(WINDOW_WIDTH)
	{
	}
	~ObstacleHandler()
	{
		box1.~Box();
		box2.~Box();
	}

	void Update(const Time& time)
	{
		box1.Update(time);
		box2.Update(time);
	}

	void Render()
	{
		box1.Render();
		box2.Render();
	}

	bool isColliding(const Golden::Collider& other)
	{
		return box1.collider.CheckColliding(other) || box2.collider.CheckColliding(other);
	}

public:
	Box box1;
	Box box2;
};