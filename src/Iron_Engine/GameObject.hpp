#pragma once

class GameObject
{
public:
	GameObject()
	{

	}

	virtual ~GameObject()
	{

	}

	virtual void Update(const Time& time) {}

	virtual void Render(Camera& camera) {}
public:
	Transform transform;
};