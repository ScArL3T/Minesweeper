#ifndef CELL_H
#define CELL_H

#include "StateManager.h"
#include "GameObject.h"

class Cell : public GameObject
{
public:
	Cell();
	~Cell();

	bool isRevealed();

	void setSize(sf::Vector2f size);
	void setTexture(sf::Texture &texture);
	void setState(sf::Uint32 state);

	sf::Uint32 getState();
	
	enum
	{
		None = 0,
		Mine = 1
	};
private:
	void update(sf::RenderWindow &window, float dt);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);
	//void collision(GameObject &go);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Texture m_texture;
	sf::Vector2f m_size;
	//sf::RectangleShape m_shape;
	sf::VertexArray m_quad;
	sf::Uint32 m_state;

	//MISC
	bool revealed;
	bool hovered, left_clicked, right_clicked;
};

#endif