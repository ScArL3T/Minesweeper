#include "PlayState.h"
#include "MenuState.h"

PlayState::~PlayState()
{

}

void PlayState::init(sf::RenderWindow &window)
{
	switch (m_difficulty)
	{
	case Difficulty::Easy:
		grid.setGridSize({ 9, 9 });
		//window.setSize({ 288, 288 });
		break;
	case Difficulty::Intermediate:
		grid.setGridSize({ 16, 16 });
		//window.setSize({ 512, 512 });
		break;
	case Difficulty::Hard:
		grid.setGridSize({ 30, 16 });
		//window.setSize({ 960, 512 });
		break;
	}
	
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
	grid.handleEvents(window, event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		state_manager.setNextState(std::make_unique<MenuState>());
}