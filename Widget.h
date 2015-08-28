#ifndef WIDGET_H
#define WIDGET_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace gui
{
	class Widget: public sf::Drawable, public sf::Transformable
	{
	public:
		//typedef std::shared_ptr<Widget> Ptr;
		virtual ~Widget() {};

		virtual void handleEvents(sf::RenderWindow &window, sf::Event &event) = 0;
		virtual void setFont(sf::Font &font) = 0;
		virtual void update(sf::RenderWindow &window) = 0;
	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0; 
	};
}

#endif