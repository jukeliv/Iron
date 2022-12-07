#pragma once

#include "Matloon.hpp"
#include <iostream>

class Random
{
public:
	static float random_value(const double& min, const double& max, const uint32_t& seed = 0)
	{
		if (seed)
			srand(seed);

		float r = (float)rand() / RAND_MAX;

		r = Matloon::map(r, 0, 1, min, max);

		return r;
	}
};
