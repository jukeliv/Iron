#pragma once

#include "Mascot.cpp"
#include "Box.cpp"

class MainGame : public Game
{
public:
	//First frame after initializing SDL 2
	MainGame()
	{
	}

	//When the program is shuting down
	~MainGame()
	{
		mascot.~Mascot();
		box.~Box();
	}

	//Every Frame ( Manage Logic )
	void Update()
	{
		mascot.Update(input, time);
		box.Update();
	}

	//Process SDL2 Events (Extra input related code...)
	void ProcessEvents(const SDL_Event& e)
	{
	}

	//Every Frame ( Draw Images )
	void Render()
	{
		if (!mascot.collider.CheckColliding(box.collider))
			mascot.Render();
		box.Render();
	}

	void RenderUI()
	{
	}
public:
	Box box;
	Mascot mascot;
};