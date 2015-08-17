#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"

class StateManager
{
public:
	StateManager();

	//Initiate the state manager
	void initStateManager(sf::RenderWindow &window, sf::Event &event);

	//Transit between states
	void changeState(std::unique_ptr<State> state);
	void pushState(std::unique_ptr<State> state);
	void popState();

	//Actions within game loop
	void update(float dt);
	void draw();
	void handleEvents();
private:
	//Check if the state is already inside the vector
	bool isInside(std::unique_ptr<State> state);

	//State vector
	std::vector<std::unique_ptr<State>> states;
	sf::RenderWindow *window; //Window
	sf::Event		 *event;  //Event

	//Main state
	const unsigned int MAINSTATE = 0;
};

//Global manager
extern StateManager state_manager;

#endif