#include "Engine.h"
#include "SplashScreen.h"
#include "MenuState.h"

SplashScreen     splash;
Engine	     	 engine;
StateManager     state_manager;

sf::SoundBuffer  clickBuffer, hoverBuffer;
sf::Sound		 clickSound, hoverSound;

sf::Font font;

//fix console. initiate it only ONCE -> TOP, use enum maybe
//highscore system
//AI
//replays
//debugger
//save game
//script engine: lua -> top
//lighting system
//fps counter in while -> top
//physics

int main()
{
	//Load extern

	font.loadFromFile("data/font.ttf");
	//clickBuffer.loadFromFile("data/click.ogg");
	//hoverBuffer.loadFromFile("data/hover.ogg");

	engine.initGame();
	engine.runGame();

	return 0;
}