#include "Engine.h"
#include "MenuState.h"

void Engine::initGame()
{
	//Initiate the window and set the framerate
	window.create({ 800, 500 }, "Minesweeper");
	window.setFramerateLimit(FPS);

	//Initiate the state manager
	state_manager.initStateManager(window, event);
	state_manager.changeState(std::unique_ptr<State>(std::make_unique<MenuState>()));
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
		state_manager.handleEvents();

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

		//Clear the window
		window.clear();

		//Update and draw current state
		state_manager.update(dt);
		state_manager.draw();

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