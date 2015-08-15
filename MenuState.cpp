#include "MenuState.h"
#include "PlayState.h"

void MenuState::init(sf::RenderWindow &window)
{
	gui.setGlobalFont(font);

	WIDTH = window.getSize().x;
	HEIGHT = window.getSize().y;

	std::string path("data/button/");
	
	playButton = gui::Button::create("Play");
	playButton->loadTextures(path + "1normal.png", path + "1hover.png", path + "1click.png");
	playButton->setPosition({ WIDTH / 2 - playButton->getSize().x / 2, HEIGHT / 2 - playButton->getSize().y });
	playButton->setOnHover(MenuState::onHover);
	playButton->setOnClick(MenuState::onClick);

	quitButton = gui::Button::create("Quit");
	quitButton->loadTextures(path + "2normal.png", path + "2hover.png", path + "2click.png");
	quitButton->setPosition({ WIDTH / 2 - quitButton->getSize().x / 2, HEIGHT / 2 + quitButton->getSize().y });
	quitButton->setOnHover(MenuState::onHover);
	//quitButton->setOnClick(MenuState::onClick);

	gui.addWidget(playButton);
	gui.addWidget(quitButton);

	playState = false;
}

void MenuState::update(sf::RenderWindow &window, float dt)
{
	gui.update(window);

	switch (quitButton->getState())
	{
	case gui::Button::LeftMousePressed:
		window.close();
		break;
	default:
		break;
	}

	switch (playButton->getState())
	{
	case gui::Button::LeftMousePressed:
		state_manager.changeState(std::unique_ptr<State>(std::make_unique<PlayState>()));
		break;
	default:
		break;
	}
}

void MenuState::draw(sf::RenderWindow &window)
{
	gui.draw(window);
}

void MenuState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	gui.handleEvents(window, event);
}

void MenuState::destroy(sf::RenderWindow &window)
{
	gui.removeAll();
}

void MenuState::onHover()
{
	hoverSound.play();
}

void MenuState::onClick()
{
	clickSound.play();
}