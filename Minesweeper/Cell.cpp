#include "Cell.h"


Cell::Cell()
{
	//m_shape.setFillColor(sf::Color::Blue);
	//m_shape.setSize({ 200, 20 });
	//m_shape.setPosition({ 200, 200 });

	m_quad.setPrimitiveType(sf::Quads);
	m_quad.resize(4);

	m_state = CellState::Normal;

	m_size.x = m_size.y = 0;
	m_quad[0].position = sf::Vector2f(0, 0);
	m_quad[1].position = sf::Vector2f(m_size.x, 0);
	m_quad[2].position = sf::Vector2f(m_size.x, m_size.y);
	m_quad[3].position = sf::Vector2f(0, m_size.y);

	//Bomb
	m_bomb = false;

	//MISC
	hovered = false;
	left_clicked = right_clicked = false;

	flagged = false;
	revealed = false;
}


Cell::~Cell()
{
}

void Cell::setSize(sf::Vector2f size)
{
	m_size = size;
	m_quad[0].position = sf::Vector2f(getPosition().x, getPosition().y);
	m_quad[1].position = sf::Vector2f(getPosition().x + m_size.x, getPosition().y);
	m_quad[2].position = sf::Vector2f(getPosition().x + m_size.x, getPosition().y + m_size.y);
	m_quad[3].position = sf::Vector2f(getPosition().x, getPosition().y + m_size.y);
}

void Cell::setTexture(sf::Texture &texture)
{
	m_texture = texture;

	m_quad[0].texCoords = sf::Vector2f(0, 0);
	m_quad[1].texCoords = sf::Vector2f(static_cast<float>(m_texture.getSize().x), 0);
	m_quad[2].texCoords = sf::Vector2f(static_cast<float>(m_texture.getSize().x), static_cast<float>(m_texture.getSize().y));
	m_quad[3].texCoords = sf::Vector2f(0, static_cast<float>(m_texture.getSize().y));
}

void Cell::setBomb(bool bomb)
{
	m_bomb = bomb;
}

void Cell::setState(CellState state)
{
	m_state = state;
}

bool Cell::isBomb()
{
	return m_bomb;
}

Cell::CellState Cell::getState()
{
	return m_state;
}

void Cell::update(sf::RenderWindow &window, float dt)
{

}

void Cell::handleEvents(sf::RenderWindow &window, sf::Event &event)
{
	if (m_state != CellState::Revealed)
	{
		//Get the rect of the quad
		sf::FloatRect bounds(getPosition().x, getPosition().y, m_size.x, m_size.y);

		//Check if the mouse is over the quad
		if (bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			hovered = true;

			//Check if the left mouse button is being pressed
			if (hovered && event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Button::Left) 
			{
				left_clicked = true;
			}
			//Check if the left mouse button is then released
			else if (left_clicked && event.type == sf::Event::MouseButtonReleased
				&& event.mouseButton.button == sf::Mouse::Button::Left)
			{
				left_clicked = false;

				if (hovered)
				{
					//Make the cell revealed
					m_state = CellState::Revealed;
				}
			}

			//Check if the right mouse button is being pressed
			if (hovered && event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Button::Right)
			{
				right_clicked = true;
			}
			//Check if the right mouse button is then released
			else if (right_clicked && event.type == sf::Event::MouseButtonReleased
				&& event.mouseButton.button == sf::Mouse::Button::Right)
			{
				right_clicked = false;

				if (hovered)
				{
					//Make the cell flagged/unflagged
					if (m_state != CellState::Flagged)
						m_state = CellState::Flagged;
					else m_state = CellState::Normal;
				}
			}
		}
		else
		{
			hovered = false;
			//m_state = Normal;
		}
	}
}

void Cell::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = &m_texture;
	target.draw(m_quad, states);
}