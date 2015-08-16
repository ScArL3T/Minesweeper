#include "MenuState.h"
#include "PlayState.h"

void MenuState::init(sf::RenderWindow &window)
{
	gui.setGlobalFont(font);

	WIDTH = window.getSize().x;
	HEIGHT = window.getSize().y;

	std::string path("data/button/");

	//Background color
	m_backgr.setSize({ WIDTH, HEIGHT });
	m_backgr.setFillColor(sf::Color(100, 180, 255));

	//Title
	m_title.setFont(font);
	m_title.setColor(sf::Color::White);
	m_title.setCharacterSize(30);
	m_title.setString("Minesweeper");
	m_title.setPosition({ WIDTH / 2 - m_title.getLocalBounds().width / 2, HEIGHT / 2 - m_title.getLocalBounds().height * 5.65f });

	//Menu panel
	m_panelTexture.loadFromFile("data/panel.png");
	m_panelSprite.setTexture(m_panelTexture);
	m_panelSprite.setPosition({ WIDTH / 2 - m_panelTexture.getSize().x / 2, HEIGHT / 2 - m_panelTexture.getSize().y / 2 });
	
	//Play button
	playButton = gui::Button::create("Play");
	playButton->loadTextures(path + "1normal.png", path + "1hover.png", path + "1click.png");
	playButton->setPosition({ WIDTH / 2 - playButton->getSize().x / 2, HEIGHT / 2 - playButton->getSize().y / 4 * 3 });
	playButton->setOnHover(MenuState::onHover);
	playButton->setOnClick(MenuState::onClick);

	//Quit button
	quitButton = gui::Button::create("Quit");
	quitButton->loadTextures(path + "2normal.png", path + "2hover.png", path + "2click.png");
	quitButton->setPosition({ WIDTH / 2 - quitButton->getSize().x / 2, HEIGHT / 2 + quitButton->getSize().y / 4 * 3 });
	quitButton->setOnHover(MenuState::onHover);
	//quitButton->setOnClick(MenuState::onClick);

	//Add widgets to the gui
	gui.addWidget(playButton);
	gui.addWidget(quitButton);

	playState = false;
}

void MenuState::update(sf::RenderWindow &window, float dt)
{
	//Update gui
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
	//Draw
	window.draw(m_backgr);
	window.draw(m_panelSprite);
	window.draw(m_title);
	gui.draw(window);
}

void MenuState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//Handle events
	gui.handleEvents(window, event);
}

void MenuState::destroy(sf::RenderWindow &window)
{
	//Remove widgets
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