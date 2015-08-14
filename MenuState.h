#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "StateManager.h"

class MenuState : public State
{
public:
	void init(sf::RenderWindow &window) override;
	void update(sf::RenderWindow &window, float dt) override;
	void draw(sf::RenderWindow &window) override;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override;
	void destroy(sf::RenderWindow &window) override;

private:
	unsigned int	  WIDTH, HEIGHT;
	bool			  playState;
};

#endif