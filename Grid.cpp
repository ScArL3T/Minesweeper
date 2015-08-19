#include "Grid.h"


Grid::Grid()
{
	t.loadFromFile("data/tileset_gray.png", sf::IntRect(0, 0, 64, 64));

	te.loadFromFile("data/tileset_gray.png", sf::IntRect(128, 0, 64, 64));
}

Grid::~Grid()
{
}

void Grid::setGridSize(unsigned int size)
{
	m_size = size;
	grid.resize(m_size, std::vector<Cell>(m_size));
	autoPosition();
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
			//if (grid[i][j].getState() == Cell::Flagged)
			//{
				grid[i][j].update(window, dt);
				//grid[i][j].setTexture(te);
				//grid[i][j].setPosition({ static_cast<float>(i * t.getSize().x), static_cast<float>(j * t.getSize().y) });
			//}
		}
	}
}

void Grid::draw(sf::RenderWindow &window)
{
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
			grid[i][j].setTexture(t);
			grid[i][j].setPosition({ static_cast<float>(i * t.getSize().x + 1), static_cast<float>(j * t.getSize().y + 1) });
		}
	}
}