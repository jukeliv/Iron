#pragma once

//IRON
#include "Iron_Engine/Core.hpp"
#include "Iron_Engine/Utils/Input.hpp"

enum class Event{SwitchGame};

class Game
{
public:
	//First frame after initializing SDL 2
	Game()
		:delta_time(0)
	{
	}

	//When the program is shuting down
	virtual ~Game(){}

	//Every Frame ( Manage Logic )
	virtual void Update(){}

	virtual void ProcessEvents(const SDL_Event& e)
	{
		uint32_t key = e.key.keysym.sym;

		switch (e.type)
		{
		case SDL_KEYDOWN:
			input.keys[key] = true;
			break;
		case SDL_KEYUP:
			input.keys[key] = false;
			break;
		}
	}

	//Every Frame ( Draw Images )
	virtual void Render(){}

	//Every Frame ( Draw UI with Dear ImGui )
	virtual void RenderUI() {}
public:
	Input input;//DO NOT REMOVE THIS!!!
	double delta_time;
};