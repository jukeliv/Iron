#pragma once

#include <iostream>
#include "Mathf.hpp"

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
