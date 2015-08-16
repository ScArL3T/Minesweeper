#ifndef ENGINE_H
#define ENGINE_H

#include "StateManager.h"
#include <time.h>
#include <string>

class Engine
{
public:
	//Initiate and run the game
	void initGame();
	void runGame();

private:
	//Handle game events
	void handleEvents();

	//Game loop
	void gameLoop();

	//Screenshot function
	void takeScreenshot();

	sf::RenderWindow window;
	sf::Event	     event;
};

#endif