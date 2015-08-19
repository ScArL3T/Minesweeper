#ifndef GRID_H
#define GRID_H

#include "Cell.h"

class Grid
{
public:
	Grid();
	~Grid();

	void setGridSize(unsigned int size);
	void setTexture(sf::Texture &texture);

	unsigned int getGridSize();

	void update(sf::RenderWindow &window, float dt);
	void draw(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);
private:
	//Recalculate position
	void autoPosition();

	//Cells matrix
	std::vector<std::vector<Cell>> grid;

	//Matrix size
	unsigned int m_size;

	sf::Texture t;

	sf::Texture te;
};

#endif