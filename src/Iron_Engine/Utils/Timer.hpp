#pragma once

#include <string_view>
#include "Iron_Engine/Core.hpp"

class Timer
{
public:
	Timer()
	{

	}

	inline void start_timer()
	{
		start = SDL_GetTicks();
	}

	inline void end_timer()
	{
		end = SDL_GetTicks();
	}

	float elapsed_time()
	{
		if(end > start)
			return end - start;
		return NULL;
	}

public:
	uint32_t start;
	uint32_t end;
};