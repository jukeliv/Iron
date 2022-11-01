#pragma once

//IRON
#include "Iron_Engine/Core.hpp"
#include "Iron_Engine/Utils/Input.hpp"

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

	//Every Frame ( Draw Images )
	virtual void Render(){}

	//Every Frame ( Draw UI with Dear ImGui )
	virtual void RenderUI() {}
public:
	Input input;//DO NOT REMOVE THIS!!!
	double delta_time;
};