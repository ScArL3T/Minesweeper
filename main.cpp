#include "Engine.h"
#include "SplashScreen.h"
#include "MenuState.h"

SplashScreen     splash;
Engine	     	 engine;
StateManager     state_manager;

sf::SoundBuffer  clickBuffer, hoverBuffer;
sf::Sound		 clickSound, hoverSound;

Difficulty m_difficulty;

sf::Font font;

//state manager: current state = last pushed state
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

	//Font
	font.loadFromFile("data/font.ttf");

	//Click sound
	clickBuffer.loadFromFile("data/click.ogg");
	clickSound.setBuffer(clickBuffer);

	//Hover sound
	hoverBuffer.loadFromFile("data/mouseover.ogg");
	hoverSound.setBuffer(hoverBuffer);

	//Init the game and run
	engine.initGame();
	engine.runGame();

	return 0;
}