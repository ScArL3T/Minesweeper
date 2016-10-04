#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

class StateManager
{
public:
	StateManager();

	//Check if there is a new state waiting in queue
	void checkState(sf::RenderWindow &window);

	//Transit between states
	void setNextState(std::unique_ptr<State> state);
	void pushState(std::unique_ptr<State> state);
	void popState();

	//Actions within game loop
	void update(sf::RenderWindow &window, float dt);
	void draw(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);
private:
	//Check if the state is already inside the vector
	bool isInside(std::unique_ptr<State> temp_state);

	//State vector
	std::vector<std::unique_ptr<State>> m_states;

	std::unique_ptr<State> m_temp;
};

//Global manager
extern StateManager state_manager;

#endif