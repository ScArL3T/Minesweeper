#include "StateManager.h"

StateManager::StateManager()
{
}

void StateManager::changeState(sf::RenderWindow &window, std::unique_ptr<State> state)
{
	//If the vector isn't empty destroy the current states
	//Clear the vector
	if (!states.empty())
	{
		states.clear();
	}

	//Move the new state inside the vector
	states.push_back(std::move(state));

	//Initiate the state
	if (!states.empty())
	{
		states.front()->init(window);
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
		states.pop_back();
	}
}

void StateManager::update(sf::RenderWindow &window, float dt)
{
	//Update the states
	if (!states.empty())
	{
		for (unsigned int i = 0; i < states.size(); i++)
		{
			states[i]->update(window, dt);
		}
	}
}

void StateManager::draw(sf::RenderWindow &window)
{
	//Draw the states
	if (!states.empty())
	{
		for (unsigned int i = 0; i < states.size(); i++)
		{
			states[i]->draw(window);
		}
	}
}

void StateManager::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//Handle the states' events
	if (!states.empty())
	{
		for (unsigned int i = 0; i < states.size(); i++)
		{
			states[i]->handleEvents(window, event);
		}
	}
}

bool StateManager::isInside(std::unique_ptr<State> state)
{
	//Check if the state is already inside the vector
	for (unsigned int i = 0; i < states.size(); i++)
	{
		if (states[i].get() == state.get())
		{
			return true;
		}
	}
	return false;
}