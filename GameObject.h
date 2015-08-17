#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "State.h"

class GameObject : public sf::Shape
{
public:
	virtual void update(sf::RenderWindow &window, float dt) = 0;
	virtual void collision(GameObject &go) = 0;

	bool checkCollision(GameObject &go)
	{
		return this->getGlobalBounds().intersects(go.getGlobalBounds());
	}

	std::vector<GameObject> GameObjects; //TODO
};

#endif