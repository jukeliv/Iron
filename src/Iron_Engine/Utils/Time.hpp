#pragma once
class Time
{
public:
	void step(const float& _delta)
	{
		delta = _delta;
		elapsed += _delta;
	}
public:
	float elapsed = 0;
	float delta = 0;
};