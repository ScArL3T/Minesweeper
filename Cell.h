#ifndef CELL_H
#define CELL_H

#include "StateManager.h"
#include "GameObject.h"

class Cell : public GameObject
{
public:
	Cell();
	~Cell();

	void update(sf::RenderWindow &window, float dt);
	void setSizee(sf::Vector2f size);

private:
	sf::Vector2f m_size;
	sf::Texture  m_texture;
	
};

#endif