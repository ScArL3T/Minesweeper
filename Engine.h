#ifndef ENGINE_H
#define ENGINE_H

#include "StateManager.h"
#include "SplashScreen.h"
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

	sf::RenderWindow window; //Window
	sf::Event	     event;  //Event

	//Icon
	sf::Image m_icon;

	//Cursor
	sf::Texture m_cursorTexture;
	sf::Sprite  m_cursorSprite;

	//SplashScreen
	SplashScreen splash;
};

#endif