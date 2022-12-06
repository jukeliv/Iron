#pragma once
#include "Mathf.hpp"

#include <iostream>

class Random
{
public:
	static float random_value(const double& min, const double& max, const uint32_t& seed = 0)
	{
		//if (seed)
			//do something
		float r = (float)rand() / RAND_MAX;
		Mathf::map(r, -1, 1, min, max);

		return r;
	}
};
