#ifndef CELL_H
#define CELL_H

#include "StateManager.h"
#include "GameObject.h"

class Cell: public GameObject
{
public:
	Cell();
	~Cell();

	enum class CellState
	{
		Normal = 0,
		Revealed,
		Flagged,
	};

	//Setters

	void setSize(sf::Vector2f size);
	void setTexture(sf::Texture &texture);
	void setBomb(bool bomb);
	void setState(CellState state);

	//Check if the cell is a bomb
	bool isBomb();

	//Get current state
	CellState getState();
	
	void handleEvents(sf::RenderWindow &window, sf::Event &event);

	//Public bools
	bool flagged, revealed;

	
private:
	//Update
	void update(sf::RenderWindow &window, float dt);

	//Draw
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	sf::Texture     m_texture; //Cell texture
	sf::Vector2f    m_size;    //Cell size
	sf::VertexArray m_quad;    //Cell shape
	CellState       m_state;   //Cell state

	//Bomb
	bool m_bomb;

	//MISC
	bool hovered, left_clicked, right_clicked;
};

#endif