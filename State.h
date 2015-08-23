#ifndef STATE_H
#define STATE_H

#include "Globals.h"

class State: sf::NonCopyable
{
public:
	virtual ~State() {};
	virtual void init(sf::RenderWindow &window) = 0;
	virtual void update(sf::RenderWindow &window, float dt) = 0;
	virtual void draw(sf::RenderWindow &window) = 0;
	virtual void handleEvents(sf::RenderWindow &window, sf::Event &event) = 0;
};

#endif