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
				if (grid[i][j].isBomb())
				{
					grid[i][j].revealed = !grid[i][j].revealed;
					grid[i][j].setTexture(m_textureBomb);
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

int Grid::countNeighbours(int x, int y)
{
	int count = 0;

	//Directions
	const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
	const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

	for (int d = 0; d < 8; d++)
	{
		int i = x + dx[d];
		int j = y + dy[d];

		//Check if the new position is inside the grid
		if (i >= 0 && i < m_size && j >= 0 && j < m_size)
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
	if (x < 0 || x >= m_size || y < 0 || y >= m_size)
		return;

	//If the cell is a bomb return
	if (grid[x][y].isBomb())
		return;

	//If the cell is flagged return
	if (grid[x][y].getState() == Cell::Flagged)
		return;

	//Count the neighbours
	int count = countNeighbours(x, y);

	//If count is greater than 0 reveal the cell and
	//set the corresponding texture
	if (count > 0)
	{
		grid[x][y].setState(Cell::Revealed);
		grid[x][y].revealed = true;
		setCountTexture(count, x, y);
	}
	else
	{
		//Else reveal the cell and execute the algorithm
		if (!grid[x][y].revealed)
		{
			grid[x][y].setState(Cell::Revealed);
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