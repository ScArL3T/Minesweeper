#include "PlayState.h"
#include "MenuState.h"

PlayState::~PlayState()
{

}

void PlayState::init(sf::RenderWindow &window)
{
	grid.setGridSize({ 16, 16 });
}

void PlayState::update(sf::RenderWindow &window, float dt)
{
	grid.update(window, dt);
	if (grid.playerWon())
	{

	}
	else if (grid.playerLost())
	{

	}
}

void PlayState::draw(sf::RenderWindow &window)
{
	grid.draw(window);
}

void PlayState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		state_manager.setNextState(std::make_unique<MenuState>());
	grid.handleEvents(window, event);
}