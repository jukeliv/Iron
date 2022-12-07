#pragma once

//IRON
#include <Iron_Engine/Engine.hpp>

class Game
{
public:
	//First frame after initializing SDL 2
	Game()
	{
	}

	//When the program is shuting down
	virtual ~Game() {}

	//Every Frame ( Manage Logic )
	virtual void Update() {}

	//Every Frame ( Process extra SDL_Events for input and more )
	virtual void ProcessEvents(const SDL_Event& e) {}

	//Every Frame ( Draw Images )
	virtual void Render() {}

	//Every Frame ( Draw UI with Dear ImGui )
	virtual void RenderUI() {}

public:
	/*DO NOT REMOVE THESE VARIABLES!!!*/

	Time time;
	Input input;
};