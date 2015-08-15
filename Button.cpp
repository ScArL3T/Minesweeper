#include "Button.h"


namespace gui
{
	Button::Button()
	{
		//Default size
		m_size.x = 120;
		m_size.y = 30;
		m_shape.setSize(m_size);

		//Set the current state
		m_state = Button::None;

		//MISC
		hovered = clicked = false;
		loaded = false;
		font_loaded = false;

		m_onClick = nullptr;
		m_onHover = nullptr;
	}

	Button::~Button()
	{
		//Destructor
	}

	Button::Ptr Button::create(const sf::String string)
	{
		auto button = std::make_shared<Button>();
		button->setString(string);
		button->setStringColor(sf::Color::White);

		return button;
	}

	void Button::setOnClick(function f)
	{
		m_onClick = f;
	}

	void Button::setOnHover(function f)
	{
		m_onHover = f;
	}

	bool Button::loadTextures(sf::String normal, sf::String hover, sf::String click)
	{
		//If the textures are loaded then update button size
		if (m_normalT.loadFromFile(normal)
			&& m_hoverT.loadFromFile(hover)
			&& m_clickT.loadFromFile(click))
		{
			m_shape.setTexture(&m_normalT);
			loaded = true;
			updateSize();
			return true;
		}
		//loaded = false;
		return false;
	}

	void Button::setColor(sf::Color color)
	{
		//Set the background color
		m_shapeColor = color;
		m_shape.setFillColor(m_shapeColor);
	}

	void Button::setStringColor(sf::Color color)
	{
		//Set the string color
		m_stringColor = color;
		m_text.setColor(m_stringColor);
	}

	void Button::setString(sf::String string)
	{
		//Set the string
		m_string = string;

		//If the font is loaded then calculate text size
		if (font_loaded)
		{
			font_loaded = false;
			m_text.setString(m_string);


			//Calculate a possible text size
			float s = m_size.y * 0.75f;
			setCharSize(static_cast<unsigned int>(s));

			//Make the text smaller if too big
			if (m_text.getLocalBounds().width > (m_size.x * 0.8f))
				setCharSize(static_cast<unsigned int>(s * m_size.x * 0.8f / m_text.getLocalBounds().width));

			//Set the position
			sf::FloatRect rect = m_text.getGlobalBounds();
			m_text.setOrigin(rect.left, rect.top);
			m_text.setPosition({ m_size.x / 2 - rect.width / 2,
				m_size.y / 2 - rect.height / 2 });
		}

	}

	void Button::setSize(sf::Vector2f size)
	{
		//Set size
		m_size = size;
		m_shape.setSize(m_size);
	}

	void Button::setFont(sf::Font &font)
	{
		//Set font
		m_font = font;
		m_text.setFont(m_font);
		font_loaded = true;
		setString(m_string);
	}

	void Button::setCharSize(unsigned int size)
	{
		//NOT WORKING
		//Set string character size
		m_charSize = size;
		m_text.setCharacterSize(m_charSize);
	}

	const sf::Color Button::getColor()
	{
		//Returns the background's color
		return m_shapeColor;
	}

	const sf::Color Button::getStringColor()
	{
		//Returns the string's color
		return m_stringColor;
	}

	const sf::String Button::getString()
	{
		//Returns the string
		return m_string;
	}

	const sf::Vector2f Button::getSize()
	{
		//Returns the size
		return m_size;
	}

	const sf::Font Button::getFont()
	{
		//Returns the font
		return m_font;
	}

	const sf::Uint32 Button::getState()
	{
		//Returns the current state of the button
		return m_state;
	}

	void Button::update(sf::RenderWindow &window)
	{

	}

	void Button::updateSize()
	{
		//If textures were loaded then resize the button
		if (loaded)
		{
			loaded = false;
			setSize({ static_cast<float>(m_normalT.getSize().x),
				static_cast<float>(m_normalT.getSize().y) });
			setString(m_string);
		}
	}

	void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		//Draw the button
		states.transform *= getTransform();
		target.draw(m_shape, states);
		target.draw(m_text, states);
	}

	void Button::handleEvents(sf::RenderWindow &window, sf::Event &event)
	{
		//Get the rect of the button
		sf::FloatRect bounds(getPosition().x, getPosition().y, m_size.x, m_size.y);
		//Check if the mouse is over the button
		if (bounds.contains(sf::Vector2f(sf::Mouse::getPosition(window))))
		{
			m_state = Button::MouseEntered;

			//Execute m_onHover() function *once*
			if (!hovered)
			{
				hovered = true;
				m_shape.setTexture(&m_hoverT);

				if (m_onHover != nullptr)
				{
					m_onHover();
				}
			}

			//Check if the left mouse button is being pressed
			if (hovered && event.type == sf::Event::MouseButtonPressed
				&& event.mouseButton.button == sf::Mouse::Button::Left)
			{
				clicked = true;
				m_shape.setTexture(&m_clickT);
			}
			//Check if the left mouse button is then released
			else if (clicked && event.type == sf::Event::MouseButtonReleased
				&& event.mouseButton.button == sf::Mouse::Button::Left)
			{
				clicked = false;

				//Execute m_onClick() function *once*
				if (hovered)
				{
					m_state = Button::LeftMousePressed;

					if (m_onClick != nullptr)
					{
						m_onClick();
					}
				}
			}
		}
		else
		{
			//Set everything back to normal
			hovered = false;
			m_state = Button::None;
			m_shape.setTexture(&m_normalT);
		}
	}
}