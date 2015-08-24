#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "StateManager.h"
#include "Grid.h"

class PlayState: public State
{
public:
	~PlayState();
	void init(sf::RenderWindow &window)							  override final;
	void update(sf::RenderWindow &window, float dt)				  override final;
	void draw(sf::RenderWindow &window)							  override final;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override final;
private:
	//Game grid
	Grid grid;
};

#endif