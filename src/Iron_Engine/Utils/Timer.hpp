#pragma once

#include <string_view>
#include <Iron_Engine/Core.hpp>

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

	Uint32 elapsed_time()
	{
		if(end > start)
			return end - start;
		return NULL;
	}

public:
	Uint32 start;
	Uint32 end;
};