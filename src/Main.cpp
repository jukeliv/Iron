#include "Game.hpp"

/*
*				  REMEMBER
* "Game.h" is where you write all your logic
*/

int main(int argc, char* argv[]) 
{
	IronGL::Init();
	Game game;

	SDL_UpdateWindowSurface(IronGL::m_Window);

	SDL_Event e; 
	uint8_t quit = 0x0;

	while (!quit)
	{
		game.Update();

		while (SDL_PollEvent(&e) != 0x0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = 0xFF;
				break;
			case SDL_KEYDOWN:
				game.input.keys[e.key.keysym.sym] = 0xFF;
				break;
			case SDL_KEYUP:
				game.input.keys[e.key.keysym.sym] = 0x0;
				break;
			}
		}

		SDL_SetRenderDrawColor(IronGL::m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		SDL_RenderClear(IronGL::m_Renderer);

		game.Render();

		SDL_RenderPresent(IronGL::m_Renderer);
	}

	game.~Game();

	IronGL::Shutdown();

	exit(0x0);
}