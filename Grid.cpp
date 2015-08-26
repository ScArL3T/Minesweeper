#include "Grid.h"


Grid::Grid()
{
	//Load textures

	m_textureNormal.loadFromFile("data/tileset_gray.png", sf::IntRect(0, 0, 64, 64));
	m_textureFlag.loadFromFile("data/tileset_gray.png", sf::IntRect(128, 0, 64, 64));
	m_textureBomb.loadFromFile("data/tileset_gray.png", sf::IntRect(192, 0, 64, 64));
	m_textureClicked.loadFromFile("data/tileset_gray.png", sf::IntRect(256, 0, 64, 64));
	m_textureOne.loadFromFile("data/tileset_gray.png", sf::IntRect(320, 0, 64, 64));
	m_textureTwo.loadFromFile("data/tileset_gray.png", sf::IntRect(384, 0, 64, 64));
	m_textureThree.loadFromFile("data/tileset_gray.png", sf::IntRect(448, 0, 64, 64));
	m_textureFour.loadFromFile("data/tileset_gray.png", sf::IntRect(512, 0, 64, 64));
	m_textureFive.loadFromFile("data/tileset_gray.png", sf::IntRect(576, 0, 64, 64));
	m_textureSix.loadFromFile("data/tileset_gray.png", sf::IntRect(640, 0, 64, 64));
	m_textureSeven.loadFromFile("data/tileset_gray.png", sf::IntRect(704, 0, 64, 64));
	m_textureEight.loadFromFile("data/tileset_gray.png", sf::IntRect(768, 0, 64, 64));

	m_size.x = m_size.y = 0;
	m_bombCount = 0;
	m_playerLost = m_playerWon = false;
}

Grid::~Grid()
{
}

void Grid::setGridSize(sf::Vector2u size)
{
	m_size = size;
	grid.resize(m_size.x, std::vector<Cell>(m_size.y));

	setBombCount();
	autoPosition();
	generateBombs();
}

const sf::Vector2u Grid::getGridSize()
{
	return m_size;
}

void Grid::update(sf::RenderWindow &window, float dt)
{
	if (!m_playerLost && !m_playerWon)
	{
		//Check if player won
		if (getNormalCells() == m_bombCount)
		{
			//PLAYER WON
			m_playerWon = true;
		}

		for (unsigned int i = 0; i < m_size.x; i++)
		{
			for (unsigned int j = 0; j < m_size.y; j++)
			{
				if (grid[i][j].getState() != Cell::CellState::Revealed)
				{
					if (grid[i][j].getState() == Cell::CellState::Flagged && !grid[i][j].flagged)
					{
						grid[i][j].flagged = !grid[i][j].flagged;
						grid[i][j].setTexture(m_textureFlag);
					}
					else if (grid[i][j].getState() == Cell::CellState::Normal && grid[i][j].flagged)
					{
						grid[i][j].flagged = !grid[i][j].flagged;
						grid[i][j].setTexture(m_textureNormal);
					}
				}
				else if (!grid[i][j].revealed)
				{
					if (grid[i][j].isBomb())
					{
						//PLAYER LOST
						m_playerLost = true;
					}
					else
					{
						if (countNeighbours(i, j) > 0)
						{
							grid[i][j].revealed = !grid[i][j].revealed;
							setCountTexture(countNeighbours(i, j), i, j);
						}
						else
						{
							floodFill(i, j);
						}
					}
				}
			}
		}
	}	
	else if (m_playerLost)
	{
		for (unsigned int i = 0; i < m_size.x; i++)
		{
			for (unsigned int j = 0; j < m_size.y; j++)
			{
				if (grid[i][j].isBomb())
				{
					grid[i][j].revealed = !grid[i][j].revealed;
					grid[i][j].setTexture(m_textureBomb);
				}
			}
		}
	}
}

void Grid::draw(sf::RenderWindow &window)
{
	//Draw grid
	for (unsigned int i = 0; i < m_size.x; i++)
	{
		for (unsigned int j = 0; j < m_size.y; j++)
		{
			window.draw(grid[i][j]);
		}
	}
}

void Grid::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	//Handle events
	for (unsigned int i = 0; i < m_size.x; i++)
	{
		for (unsigned int j = 0; j < m_size.y; j++)
		{
			grid[i][j].handleEvents(window, event);
		}
	}
}

void Grid::autoPosition()
{
	for (unsigned int i = 0; i < m_size.x; i++)
	{
		for (unsigned int j = 0; j < m_size.y; j++)
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

void Grid::setBombCount()
{
	//Set bomb count
	if (m_size.x == 9 && m_size.y == 9)
	{
		m_bombCount = 10;
	}
	else if (m_size.x == 16 && m_size.y == 16)
	{
		m_bombCount = 40;
	}
	else if (m_size.x == 30 && m_size.y == 16)
	{
		m_bombCount = 99;
	}
}

void Grid::generateBombs()
{
	//Random generators
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<unsigned int> distX(0, m_size.x - 1);
	std::uniform_int_distribution<unsigned int> distY(0, m_size.y - 1);

	for (unsigned int i = 0; i < m_bombCount; i++)
	{
		unsigned int x = distX(mt);
		unsigned int y = distY(mt);

		//If the current position is already a bomb generate new position
		while (grid[x][y].isBomb())
		{
			x = distX(mt);
			y = distY(mt);
		}

		//Set bomb
		grid[x][y].setBomb(true);
	}
}

unsigned int Grid::countNeighbours(int x, int y)
{
	unsigned int count = 0;

	//Directions
	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int d = 0; d < 8; d++)
	{
		int i = x + dx[d];
		int j = y + dy[d];

		//Check if the new position is inside the grid
		if (i >= 0 && i < m_size.x && j >= 0 && j < m_size.y)
		{
			if (grid[i][j].isBomb())
			{
				count++;
			}
		}
	}
	return count;
}

void Grid::floodFill(int x, int y)
{
	//Flood fill algorithm

	//If the cell is outside the grid return
	if (x < 0 || x >= m_size.x || y < 0 || y >= m_size.y)
		return;

	//If the cell is a bomb return
	if (grid[x][y].isBomb())
		return;

	//If the cell is flagged return
	if (grid[x][y].getState() == Cell::CellState::Flagged)
		return;

	//Count the neighbours
	int count = countNeighbours(x, y);

	//If count is greater than 0 reveal the cell and
	//set the corresponding texture
	if (count > 0)
	{
		grid[x][y].setState(Cell::CellState::Revealed);
		grid[x][y].revealed = true;
		setCountTexture(count, x, y);
	}
	else
	{
		//Else reveal the cell and execute the algorithm
		if (!grid[x][y].revealed)
		{
			grid[x][y].setState(Cell::CellState::Revealed);
			grid[x][y].revealed = true;

			grid[x][y].setTexture(m_textureClicked);

			//8 directions
			floodFill(x + 1, y);
			floodFill(x - 1, y);
			floodFill(x, y + 1);
			floodFill(x, y - 1);
			floodFill(x - 1, y - 1);
			floodFill(x - 1, y + 1);
			floodFill(x + 1, y - 1);
			floodFill(x + 1, y + 1);
		}
	}
}

void Grid::setCountTexture(int count, int x, int y)
{
	//Set the corresponding texture
	switch (count)
	{
	case 1:
		grid[x][y].setTexture(m_textureOne);
		break;
	case 2:
		grid[x][y].setTexture(m_textureTwo);
		break;
	case 3:
		grid[x][y].setTexture(m_textureThree);
		break;
	case 4:
		grid[x][y].setTexture(m_textureFour);
		break;
	case 5:
		grid[x][y].setTexture(m_textureFive);
		break;
	case 6:
		grid[x][y].setTexture(m_textureSix);
		break;
	case 7:
		grid[x][y].setTexture(m_textureSeven);
		break;
	case 8:
		grid[x][y].setTexture(m_textureEight);
		break;
	default:
		break;
	}
}

unsigned int Grid::getNormalCells()
{
	unsigned int count = 0;

	for (unsigned int i = 0; i < m_size.x; i++)
	{
		for (unsigned int j = 0; j < m_size.y; j++)
		{
			if (!grid[i][j].revealed)
			{
				count++;
			}
		}
	}
	return count;
}

bool Grid::playerWon()
{
	return m_playerWon;
}

bool Grid::playerLost()
{
	return m_playerLost;
}