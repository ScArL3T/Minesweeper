#include "PlayState.h"
#include "MenuState.h"

void PlayState::init(sf::RenderWindow &window)
{
	std::cout << "playstate init";
	c.setPosition({ 40, 0 });
	sf::Texture t;
	t.loadFromFile("data/cursor.png");
	c.setTexture(t);
	//c.setSize({ 200, 200 });

	grid.setGridSize(9);
}

void PlayState::update(sf::RenderWindow &window, float dt)
{
	grid.update(window, dt);
}

void PlayState::draw(sf::RenderWindow &window)
{
	window.draw(c);
	grid.draw(window);
}

void PlayState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//c.handleEvents(window, event);
	grid.handleEvents(window, event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		state_manager.changeState(std::unique_ptr<State>(std::make_unique<MenuState>()));
}

void PlayState::destroy(sf::RenderWindow &window)
{

}