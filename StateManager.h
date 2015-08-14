#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

#define MAINSTATE 0

class StateManager
{
public:
	StateManager();

	//Initiate the state manager
	void initStateManager(sf::RenderWindow &window, sf::Event &event); //functie separata pentru event

	//Transit between states
	void changeState(std::shared_ptr<State> state);
	void pushState(std::shared_ptr<State> state);
	void popState();

	//Actions within game loop
	void update(float dt);
	void draw();
	void handleEvents();
private:
	bool isInside(std::shared_ptr<State> state);

	std::vector<std::shared_ptr<State>> states;
	sf::RenderWindow					*window;
	sf::Event							*event;
};

extern StateManager  state_manager;

#endif