#pragma once

#include <stdlib.h>
#include "Mathf.hpp"

class Random
{
public:
	static float random_value(const double& min, const double& max)
	{
		float r = (float)rand() / RAND_MAX;
		r = r * 2.0f - 1.0f;

		Mathf::map(r, -1, 1, min, max);

		return r;
	}
};
