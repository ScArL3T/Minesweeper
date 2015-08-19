#ifndef CELL_H
#define CELL_H

#include "StateManager.h"
#include "GameObject.h"

class Cell : public GameObject
{
public:
	Cell();
	~Cell();

	void setSize(sf::Vector2f size);
	void setTexture(sf::Texture &texture);
	void setBomb(bool bomb);

	bool isBomb();

	sf::Uint32 getState();
	
	enum
	{
		None = 0,
		Revealed,
		Flagged
	};
	void update(sf::RenderWindow &window, float dt);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);
private:
	
	
	//void collision(GameObject &go);
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Texture m_texture;
	sf::Vector2f m_size;
	//sf::RectangleShape m_shape;
	sf::VertexArray m_quad;
	sf::Uint32 m_state;

	bool m_bomb;
	//MISC
	bool hovered, left_clicked, right_clicked;
	bool flagged;
	sf::Texture te;
};

#endif