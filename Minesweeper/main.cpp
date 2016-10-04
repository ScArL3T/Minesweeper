#include "Engine.h"
#include "SplashScreen.h"
#include "MenuState.h"
#include "Globals.h"

StateManager     state_manager;

sf::Sound		 clickSound, hoverSound;

Difficulty m_difficulty;

sf::Font font;

int main()
{
	//Load extern
	sf::SoundBuffer clickBuffer, hoverBuffer;
	//Font
	font.loadFromFile("data/font.ttf");

	//Click sound
	clickBuffer.loadFromFile("data/click.ogg");
	clickSound.setBuffer(clickBuffer);

	//Hover sound
	hoverBuffer.loadFromFile("data/mouseover.ogg");
	hoverSound.setBuffer(hoverBuffer);

	//Init the game and run
	Engine engine;

	engine.initGame();
	engine.runGame();

	return 0;
}