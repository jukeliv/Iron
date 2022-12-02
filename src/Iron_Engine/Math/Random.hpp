#pragma once
#include "Mathf.hpp"

#include <iostream>

class Random
{
public:
	static float random_value(const double& min, const double& max)
	{
		float r = (float)rand() / RAND_MAX;
		Mathf::map(r, -1, 1, min, max);

		return r;
	}
};
