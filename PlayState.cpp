#include "PlayState.h"
#include "MenuState.h"

PlayState::~PlayState()
{

}

void PlayState::init(sf::RenderWindow &window)
{
	m_text.setFont(font);
	m_text.setCharacterSize(window.getSize().x / 8);

	switch (m_difficulty)
	{
	case Difficulty::Easy:
		grid.setGridSize({ 9, 9 });
		break;
	case Difficulty::Intermediate:
		grid.setGridSize({ 16, 16 });
		window.setSize({ 512, 512 });
		break;
	case Difficulty::Hard:
		grid.setGridSize({ 30, 16 });
		window.setSize({ 960, 512 });
		break;
	default:
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
		m_text.setColor(sf::Color::Red);
		m_text.setString("GAME OVER!");
		m_text.setPosition(window.getSize().x / 2 - m_text.getLocalBounds().width / 2, window.getSize().y / 6 * 2);
	}
}

void PlayState::draw(sf::RenderWindow &window)
{
	grid.draw(window);
	if (grid.playerLost() || grid.playerWon())
	{
		window.draw(m_text);
	}
}

void PlayState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	grid.handleEvents(window, event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		state_manager.setNextState(std::make_unique<MenuState>());
}

void PlayState::win()
{

}

void PlayState::lose()
{

}