#pragma once

//IRON
#include <Iron_Engine/Engine.hpp>

enum class Event{SwitchGame};

class Game
{
public:
	//First frame after initializing SDL 2
	Game()
	{
	}

	//When the program is shuting down
	virtual ~Game(){}

	//Every Frame ( Manage Logic )
	virtual void Update(){}

	virtual void ProcessEvents(const SDL_Event& e){}

	//Every Frame ( Draw Images )
	virtual void Render(){}

	//Every Frame ( Draw UI with Dear ImGui )
	virtual void RenderUI() {}

public:
	Time time;
	Input input;//DO NOT REMOVE THIS!!!
};