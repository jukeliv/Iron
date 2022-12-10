#include <Iron_Engine/Engine.hpp>
#include "MainGame.cpp"

int main(int argc, char* argv[]) 
{
	/*
	* Note(JukeLiv): 
	* Hello, if you are using Iron and you want to upgrade the
	* Iron version you have, just switch "Iron_Engine" with the
	* new one and you should be ready to go cuz i'm not going to
	* change the workflow of the engine this was my last change to this
	*/
	Application app;
	app.Init();
	app.SetCurrentGame<MainGame>();
	app.Run();
        exit(0);

}
