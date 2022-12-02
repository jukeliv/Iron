#pragma once
class Time
{
public:
	void step(const double& _delta)
	{
		delta = _delta;
		elapsed += _delta;
	}
public:
	double elapsed = 0;
	double delta = 0;
};