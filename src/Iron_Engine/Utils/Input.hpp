#pragma once

#include <unordered_map>

enum class Axis {HORIZONTAL, VERTICAL};

class Input
{
public:
	Input(){}

	float getAxis(Axis axis)
	{
		switch (axis)
		{
		case Axis::HORIZONTAL:
			if (keys[SDLK_d] || keys[SDLK_RIGHT])
				return 1;
			else if (keys[SDLK_a] || keys[SDLK_LEFT])
				return -1;
			else
				return 0;

		case Axis::VERTICAL: // y is negative, so i switch up the values :/
			if (keys[SDLK_w] || keys[SDLK_UP])
				return -1;
			else if (keys[SDLK_s] || keys[SDLK_DOWN])
				return 1;
			else
				return 0;

		default:
			return NULL;
		}
	}

	std::unordered_map<uint32_t, bool> keys;
};