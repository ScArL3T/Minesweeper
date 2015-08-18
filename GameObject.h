#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "State.h"

class GameObject : public sf::Drawable, public sf::Transformable
{
public:
	virtual void update(sf::RenderWindow &window, float dt) = 0;
	virtual void handleEvents(sf::RenderWindow &window, sf::Event &event) = 0;

protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
};

#endif