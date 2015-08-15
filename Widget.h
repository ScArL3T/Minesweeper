#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace gui
{
	class Widget : public sf::Drawable, public sf::Transformable
	{
	public:
		//typedef std::shared_ptr<Widget> Ptr;

		virtual void handleEvents(sf::RenderWindow &window, sf::Event &event) = 0;
		virtual void setFont(sf::Font &font) = 0;
		virtual void update(sf::RenderWindow &window) = 0;
	protected:
		sf::RectangleShape m_shape; // Shape of the widget
		//sf::Text		   m_text; //Widget text
		//Virtual function for draw - sf::Drawable
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
		{
			/*
			states.transform *= getTransform();
			target.draw(m_shape, states);
			target.draw(m_text, states);
			*/
		}
	};
}

#endif