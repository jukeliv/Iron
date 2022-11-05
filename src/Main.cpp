#include "MainGame.cpp"
#include "Iron_Engine/Application.hpp"

int main(int argc, char* argv[]) 
{
	Application app;
	app.Init<MainGame>();

	app.Run();
}