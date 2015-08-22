#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

class StateManager
{
public:
	StateManager();

	//Transit between states
	void changeState(sf::RenderWindow &window, std::unique_ptr<State> state);
	void pushState(std::unique_ptr<State> state);
	void popState();

	//Actions within game loop
	void update(sf::RenderWindow &window, float dt);
	void draw(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);
private:
	//Check if the state is already inside the vector
	bool isInside(std::unique_ptr<State> state);

	//State vector
	std::vector<std::unique_ptr<State>> states;
};

//Global manager
extern StateManager state_manager;

#endif