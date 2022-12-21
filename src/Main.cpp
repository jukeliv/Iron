#define MINIAUDIO_IMPLEMENTATION
#define MA_NO_DEVICE_IO

#include <Iron_Engine/Engine.hpp>
#include "MainGame.cpp"

int SDL_main(int argc, char* argv[])
{
	/*
	* Note(JukeLiv):
	* Hello, if you are using Iron and you want to upgrade the
	* Iron version you have, just switch "Iron_Engine" with the
	* new one and you should be ready to go cuz i'm not going to
	* change the workflow of the engine this was my last change to this
	*/
	Application app;

	WinConfig config;

	config.title = "slime";
	config.loadFromINI("./winConfig.ini");

	app.Init(config);

	app.SetCurrentGame<MainGame>();

	app.Run();
}