#include "DifficultyState.h"
#include "MenuState.h"

DifficultyState::~DifficultyState()
{

}

void DifficultyState::init(sf::RenderWindow &window)
{
	gui.setGlobalFont(font);

	WIDTH = window.getSize().x;
	HEIGHT = window.getSize().y;

	std::string path("data/button/");

	//Background color
	m_backgr.setSize({ WIDTH, HEIGHT });
	m_backgr.setFillColor(sf::Color(100, 180, 255));

	//Easy button
	easyButton = gui::Button::create("Play");
	easyButton->loadTextures(path + "1normal.png", path + "1hover.png", path + "1click.png");
	easyButton->setPosition({ WIDTH / 2 - easyButton->getSize().x / 2, HEIGHT / 2 - easyButton->getSize().y * 2 });
	easyButton->setOnHover(DifficultyState::onHover);
	easyButton->setOnClick(DifficultyState::onClick);

	//Intermediate button
	intermButton = gui::Button::create("Play");
	intermButton->loadTextures(path + "1normal.png", path + "1hover.png", path + "1click.png");
	intermButton->setPosition({ WIDTH / 2 - intermButton->getSize().x / 2, HEIGHT / 2 - intermButton->getSize().y / 2 });
	intermButton->setOnHover(DifficultyState::onHover);
	intermButton->setOnClick(DifficultyState::onClick);

	//Hard button
	hardButton = gui::Button::create("Play");
	hardButton->loadTextures(path + "1normal.png", path + "1hover.png", path + "1click.png");
	hardButton->setPosition({ WIDTH / 2 - hardButton->getSize().x / 2, HEIGHT / 2 + hardButton->getSize().y * 2 / 4});
	hardButton->setOnHover(DifficultyState::onHover);
	hardButton->setOnClick(DifficultyState::onClick);

	gui.addWidget(easyButton);
	gui.addWidget(intermButton);
	gui.addWidget(hardButton);
}

void DifficultyState::update(sf::RenderWindow &window, float dt)
{
	gui.update(window);
}

void DifficultyState::draw(sf::RenderWindow &window)
{
	window.draw(m_backgr);
	gui.draw(window);
}

void DifficultyState::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	gui.handleEvents(window, event);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		state_manager.setNextState(std::make_unique<MenuState>());
}

void DifficultyState::onHover()
{
	hoverSound.play();
}

void DifficultyState::onClick()
{
	clickSound.play();
}