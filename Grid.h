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

	void setGridSize(sf::Vector2u size);
	void setTexture(sf::Texture &texture);

	const sf::Vector2u getGridSize();

	void update(sf::RenderWindow &window, float dt);
	void draw(sf::RenderWindow &window);
	void handleEvents(sf::RenderWindow &window, sf::Event &event);

	//Check if the player won
	bool playerWon();

	//Check if the player lost
	bool playerLost();
private:
	//Recalculate position
	void autoPosition();

	//Set bomb count
	void setBombCount();

	//Generate bombs
	void generateBombs();

	//Count neighbours
	unsigned int countNeighbours(int x, int y);

	//Flood fill algorithm
	void floodFill(int x, int y);

	//Set the corresponding texture
	void setCountTexture(int count, int x, int y);

	//Number of unrevealed cells
	unsigned int getNormalCells();

	//Cells matrix
	std::vector<std::vector<Cell>> grid;

	//Matrix size
	sf::Vector2u m_size;
	
	//Number of bombs
	unsigned int m_bombCount;
	
	//Player lost & won
	bool m_playerLost, m_playerWon;

	//Textures
	sf::Texture m_textureFlag;
	sf::Texture m_textureNormal;
	sf::Texture m_textureClicked;
	sf::Texture m_textureBomb;
	sf::Texture m_textureOne, m_textureTwo, m_textureThree, m_textureFour;
	sf::Texture m_textureFive, m_textureSix, m_textureSeven, m_textureEight;
};

#endif