#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "StateManager.h"

class PlayState: public State
{
public:
	void init(sf::RenderWindow &window) override;
	void update(sf::RenderWindow &window, float dt) override;
	void draw(sf::RenderWindow &window) override;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override;
	void destroy(sf::RenderWindow &window) override;
};

#endif