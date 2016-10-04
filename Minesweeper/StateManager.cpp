#include "StateManager.h"

StateManager::StateManager()
{
	m_temp = nullptr;
}

void StateManager::setNextState(std::unique_ptr<State> state)
{
	//Move the new state in a temporary unique_ptr
	m_temp = std::move(state);
}

void StateManager::checkState(sf::RenderWindow &window)
{
	//Check if there is a new state waiting in queue
	if (m_temp != nullptr)
	{
		//Clear the vector
		if (!m_states.empty())
		{
			m_states.clear();
		}

		//Move the new state inside the vector
		m_states.push_back(std::move(m_temp));

		//Initiate the state
		if (!m_states.empty())
		{
			m_states.front()->init(window);
		}

		//Reset the temporary unique_ptr
		m_temp.reset();  //m_temp = nullptr;
	}
}

void StateManager::pushState(std::unique_ptr<State> state)
{
	//Push state
	if (!isInside(std::move(state)))
	{
		m_states.push_back(std::move(state));
		//states[states.size() - 1]->init(*window);
	}
}

void StateManager::popState()
{
	//Pop state
	if (m_states.size() > 1)
	{
		m_states.pop_back();
	}
}

void StateManager::update(sf::RenderWindow &window, float dt)
{
	//Update the states
	if (!m_states.empty())
	{
		for (std::unique_ptr<State>& state : m_states)
		{
			state->update(window, dt);
		}
	}
}

void StateManager::draw(sf::RenderWindow &window)
{
	//Draw the states
	if (!m_states.empty())
	{
		for (std::unique_ptr<State>& state : m_states)
		{
			state->draw(window);
		}
	}
}

void StateManager::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//Handle the states' events
	if (!m_states.empty())
	{
		for (std::unique_ptr<State>& state : m_states)
		{
			state->handleEvents(window, event);
		}
	}
}

bool StateManager::isInside(std::unique_ptr<State> temp_state)
{
	//Check if the state is already inside the vector
	for (std::unique_ptr<State>& state : m_states)
	{
		if (state.get() == temp_state.get())
		{
			return true;
		}
	}
	std::cout << "already inside" << std::endl;
	return false;
}