#ifndef STATE_H
#define STATE_H

#include "Globals.h"

class State
{
public:
	virtual void init(sf::RenderWindow &window) = 0;
	virtual void update(sf::RenderWindow &window, float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void handleEvents(sf::RenderWindow &window, sf::Event &event) = 0;
	virtual void destroy(sf::RenderWindow &window) = 0;
};

#endif