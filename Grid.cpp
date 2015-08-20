#include "Grid.h"


Grid::Grid()
{
	//Load textures
	m_textureNormal.loadFromFile("data/tileset_gray.png", sf::IntRect(0, 0, 64, 64));
	m_textureFlag.loadFromFile("data/tileset_gray.png", sf::IntRect(128, 0, 64, 64));
	m_textureBomb.loadFromFile("data/tileset_gray.png", sf::IntRect(192, 0, 64, 64));
	m_textureClicked.loadFromFile("data/tileset_gray.png", sf::IntRect(256, 0, 64, 64));
}

Grid::~Grid()
{
}

void Grid::setGridSize(unsigned int size)
{
	m_size = size;
	grid.resize(m_size, std::vector<Cell>(m_size));
	autoPosition();
	generateBombs();
}

unsigned int Grid::getGridSize()
{
	return m_size;
}

void Grid::update(sf::RenderWindow &window, float dt)
{
	for (unsigned int i = 0; i < m_size; i++)
	{
		for (unsigned int j = 0; j < m_size; j++)
		{
			if (grid[i][j].getState() != Cell::Revealed)
			{
				if (grid[i][j].getState() == Cell::Flagged && !grid[i][j].flagged)
				{
					grid[i][j].flagged = !grid[i][j].flagged;
					grid[i][j].setTexture(m_textureFlag);
				}
				else if (grid[i][j].getState() == Cell::Normal && grid[i][j].flagged)
				{
					grid[i][j].flagged = !grid[i][j].flagged;
					grid[i][j].setTexture(m_textureNormal);
				}
			}
			else if (!grid[i][j].revealed)
			{
				grid[i][j].revealed = !grid[i][j].revealed;
				if (grid[i][j].isBomb())
				{
					grid[i][j].setTexture(m_textureBomb);
				}
				else
				{
					grid[i][j].setTexture(m_textureClicked);
				}
			}
		}
	}
}

void Grid::draw(sf::RenderWindow &window)
{
	//Draw grid
	for (unsigned int i = 0; i < m_size; i++)
	{
		for (unsigned int j = 0; j < m_size; j++)
		{
			window.draw(grid[i][j]);
		}
	}
}

void Grid::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//Handle events
	for (unsigned int i = 0; i < m_size; i++)
	{
		for (unsigned int j = 0; j < m_size; j++)
		{
			grid[i][j].handleEvents(window, event);
		}
	}
}

void Grid::autoPosition()
{
	for (unsigned int i = 0; i < m_size; i++)
	{
		for (unsigned int j = 0; j < m_size; j++)
		{
			//Set the size of the cell
			grid[i][j].setSize({ static_cast<float>(m_textureNormal.getSize().x / 2),
				static_cast<float>(m_textureNormal.getSize().y / 2) });

			//Set the texture
			grid[i][j].setTexture(m_textureNormal);

			//Set the position
			grid[i][j].setPosition({ static_cast<float>(i * m_textureNormal.getSize().x / 2),
				static_cast<float>(j * m_textureNormal.getSize().y / 2) });
		}
	}
}

void Grid::generateBombs()
{
	//Random generators
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<unsigned int> dist(0, m_size - 1);

	for (unsigned int i = 0; i < m_size; i++)
	{
		unsigned int x = dist(mt);
		unsigned int y = dist(mt);

		//If the current position is already a bomb generate new position
		while (grid[x][y].isBomb())
		{
			x = dist(mt);
			y = dist(mt);
		}

		//Set bomb
		grid[x][y].setBomb(true);
	}
}