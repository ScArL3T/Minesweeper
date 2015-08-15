#include "StateManager.h"

StateManager::StateManager()
{
}

void StateManager::initStateManager(sf::RenderWindow &window, sf::Event &event)
{
	//Initiate variables
	this->window = &window;
	this->event = &event;
}

void StateManager::changeState(std::unique_ptr<State> state)
{
	//If the vector isn't empty destroy the current states
	//Clear the vector
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
		{
			states[i]->destroy(*window);
		}
		states.clear();
	}

	//Move the new state inside the vector
	states.push_back(std::move(state));

	//Initiate the state
	if (states.empty() == false)
	{
		states[MAINSTATE]->init(*window);
	}
}

void StateManager::pushState(std::unique_ptr<State> state)
{
	//Push state
	if (!isInside(std::move(state)))
	{
		states.push_back(std::move(state));
		//states[states.size() - 1]->init(*window);
	}
}

void StateManager::popState()
{
	//Pop state
	if (states.size() > 1)
	{
		states[states.size() - 1]->destroy(*window);
		states.pop_back();
	}
}

void StateManager::update(float dt)
{
	//Update the states
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
			states[i]->update(*window, dt);
	}
}

void StateManager::draw()
{
	//Draw the states
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
			states[i]->draw(*window);
	}
}

void StateManager::handleEvents()
{
	//Handle the states' events
	if (states.empty() == false)
	{
		if (states.size() > 1)
			for (auto i = 1; i < states.size(); i++)
				states[i]->handleEvents(*window, *event);
		else states[MAINSTATE]->handleEvents(*window, *event);
	}
}

bool StateManager::isInside(std::unique_ptr<State> state)
{
	//Check if the state is already inside the vector
	for (auto i = 0; i < states.size(); i++)
	{
		if (states[i].get() == state.get())
		{
			return true;
		}
	}
	return false;
}