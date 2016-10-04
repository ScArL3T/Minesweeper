#ifndef GUI_H
#define GUI_H

#include "Widget.h"
#include <queue>

namespace gui
{
	class Gui
	{
	public:
		Gui();
		~Gui();

		//Add a widget to gui
		void addWidget(std::shared_ptr<Widget> widget);

		//Remove a widget - work in progress
		void removeWidget(const std::string name);

		//Update the widgets
		void update(sf::RenderWindow &window);

		//Draw the widgets
		void draw(sf::RenderWindow &window);

		//Handle events for every widget
		void handleEvents(sf::RenderWindow &window, sf::Event &event);

		//Set the font
		void setGlobalFont(sf::Font &font);

		//Remove all the widgets
		void removeAll();
	private:
		std::vector<std::shared_ptr<Widget>> widgets;
		sf::Font m_font;
	};

}

#endif