#pragma once

#include <iostream>
#include <cstdlib>

class Random
{
public:
	static float random_value(const double& min, const double& max)
	{
		float r = (float)rand() / RAND_MAX;
		r = r * 2.0f - 1.0f;

		Mathf::map(r, 0, 1, min, max);

		return r;
	}
};