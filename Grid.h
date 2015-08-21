#ifndef GRID_H
#define GRID_H

#include "Cell.h"
#include <random>

//count_neighbours function
//flood fill
//make functions for each public bool in Cell.h

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

	//Generate bombs
	void generateBombs();

	//Count neighbours
	int countNeighbours(int x, int y);

	//Flood fill algorithm
	void floodFill(int x, int y);

	void setCountTexture(int count, int x, int y);

	//Cells matrix
	std::vector<std::vector<Cell>> grid;

	//Matrix size
	unsigned int m_size;

	//Textures
	sf::Texture m_textureFlag;
	sf::Texture m_textureNormal;
	sf::Texture m_textureClicked;
	sf::Texture m_textureBomb;
	sf::Texture m_textureOne, m_textureTwo, m_textureThree, m_textureFour;
	sf::Texture m_textureFive, m_textureSix, m_textureSeven, m_textureEight;
};

#endif