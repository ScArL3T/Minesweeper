#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <string>

namespace gui
{
	class Button: public Widget
	{
	public:
		Button();
		Button(const Button& copy); //TODO
		~Button();

		//Make the button a shared pointer.
		typedef std::shared_ptr<Button> Ptr;

		//Pointer function
		typedef void(*function)();

		//Creates and returns a button
		static Button::Ptr create(const sf::String text);

		//Set click function
		void setOnClick(function f);

		//Set hover function
		void setOnHover(function f);

		//Load button textures
		bool loadTextures(sf::String normal, sf::String hover, sf::String click);

		//Set

		void setColor(sf::Color color);
		void setStringColor(sf::Color color);
		void setString(sf::String string);
		void setSize(sf::Vector2f size);
		void setFont(sf::Font &font);
		void setCharSize(unsigned int size); //Not working

		//Get

		const sf::Color getColor();
		const sf::Color getStringColor();
		const sf::String getString();
		const sf::Vector2f getSize();
		const sf::Font getFont();
		const sf::Uint32 getState();

		enum
		{
			None = 0,
			MouseEntered = 1,
			LeftMousePressed = 2
		};
	private:
		void update(sf::RenderWindow &window);
		void updateSize();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const;

		//Handle widget events
		void handleEvents(sf::RenderWindow &window, sf::Event &event);

		//Pointer functions
		function m_onClick, m_onHover;

		//Button textures
		sf::Texture m_normalT, m_hoverT, m_clickT;

		//Text and rectangle color
		sf::Color m_stringColor;
		sf::Color m_shapeColor;

		unsigned int m_charSize; //Char size
		sf::Font     m_font;	 //Font used
		sf::Vector2f m_size;	 //Button size
		sf::Uint32   m_state;	 //Button state
		sf::String   m_string;   //Button string

		sf::RectangleShape m_shape; //Button shape
		sf::Text		   m_text;  //Button text

		//MISC
		bool hovered, clicked;
		bool loaded;
		bool font_loaded;
	};
}

#endif