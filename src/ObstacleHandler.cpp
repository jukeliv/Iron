#pragma once

#include <Iron_Engine/Engine.hpp>
#include "Box.cpp"

class ObstacleHandler
{
public:
	ObstacleHandler()
		:box2(WINDOW_WIDTH * 1.5f),
		box1(WINDOW_WIDTH)
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

	void Render(Camera& camera)
	{
		box1.Render(camera);
		box2.Render(camera);
	}

	bool isColliding(const Golden::Collider& other)
	{

		if (box1.collider.CheckColliding(other)) {
			box1.Reset();
		}
		else if (box2.collider.CheckColliding(other)) {
			box2.Reset();
		}


		return box1.collider.CheckColliding(other) || box2.collider.CheckColliding(other);
	}

public:
	Box box1;
	Box box2;
};