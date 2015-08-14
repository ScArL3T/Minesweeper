#include "MenuState.h"

void MenuState::init(sf::RenderWindow &window)
{
	WIDTH = window.getSize().x;
	HEIGHT = window.getSize().y;

	playState = false;
}

void MenuState::update(sf::RenderWindow &window, float dt)
{
	
}

void MenuState::draw(sf::RenderWindow &window)
{

}

void MenuState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{

}

void MenuState::destroy(sf::RenderWindow &window)
{
	
}