#include "Engine.h"
#include "MenuState.h"

void Engine::initGame()
{
	//Initiate splashscreen
	splash.Create(255, 1.5f);

	//Initiate window and set the framerate 
	window.create({ 288, 288 }, "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(FPS);
	
	//Load and set icon
	m_icon.loadFromFile("data/icon.png");
	window.setIcon(m_icon.getSize().x, m_icon.getSize().y, m_icon.getPixelsPtr());

	//Change cursor
	window.setMouseCursorVisible(false);
	m_cursorTexture.loadFromFile("data/cursor.png");
	m_cursorSprite.setTexture(m_cursorTexture);

	//Initiate state manager
	state_manager.changeState(window, std::make_unique<MenuState>());
}

void Engine::runGame()
{
	//Game loop
	gameLoop();
}

void Engine::handleEvents()
{
	//Events
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		//Handle state manager's events
		state_manager.handleEvents(window, event);

		//Screenshot
		takeScreenshot();
	}
}

void Engine::gameLoop()
{
	sf::Clock clock;
	while (window.isOpen())
	{
		//Events
		handleEvents();

		//Delta time
		float dt = clock.restart().asSeconds();

		//Cursor position
		m_cursorSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

		//Clear the window
		window.clear();

		//Update and draw current state
		state_manager.update(window, dt);
		state_manager.draw(window);

		//Draw cursor
		window.draw(m_cursorSprite);

		//Display the window
		window.display();
	}
}

void Engine::takeScreenshot()
{
	//Save screenshot
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F10)
	{
		sf::Image ss = window.capture();
		std::string filename = "screenshots/screenshot_";
		filename.append(std::to_string(time(0)));
		filename.append(".png");
		ss.saveToFile(filename);
	}
}