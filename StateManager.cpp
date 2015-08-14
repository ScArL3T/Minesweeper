#include "StateManager.h"

StateManager::StateManager()
{
}

void StateManager::initStateManager(sf::RenderWindow &window, sf::Event &event)
{
	this->window = &window;
	this->event = &event;
}

void StateManager::changeState(std::shared_ptr<State> state)
{
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
		{
			states[i]->destroy(*window);
		}
		states.clear();
	}

	states.push_back(state);

	if (states.empty() == false)
	{
		states[MAINSTATE]->init(*window);
	}
}

void StateManager::pushState(std::shared_ptr<State> state)
{
	if (!isInside(state))
	{
		states.push_back(state);
		//states[states.size() - 1]->init(*window);
	}
}

void StateManager::popState()
{
	if (states.size() > 1)
	{
		states[states.size() - 1]->destroy(*window);
		states.pop_back();
	}
}

void StateManager::update(float dt)
{
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
			states[i]->update(*window, dt);
	}
}

void StateManager::draw()
{
	if (states.empty() == false)
	{
		for (auto i = 0; i < states.size(); i++)
			states[i]->draw(*window);
	}
}

void StateManager::handleEvents()
{
	if (states.empty() == false)
	{
		if (states.size() > 1)
			for (auto i = 1; i < states.size(); i++)
				states[i]->handleEvents(*window, *event);
		else states[MAINSTATE]->handleEvents(*window, *event);
	}
}

bool StateManager::isInside(std::shared_ptr<State> state)
{
	//Check if the state is already in the vector
	for (auto i = 0; i < states.size(); i++)
	{
		if (states[i].get() == state.get())
		{
			return true;
		}
	}
	return false;
}