#include "Gui.h"

namespace gui
{
	Gui::Gui()
	{

	}

	Gui::~Gui()
	{

	}

	void Gui::addWidget(std::shared_ptr<Widget> widget)
	{
		widget->setFont(m_font);
		widgets.push_back(widget);
	}

	void Gui::removeWidget(const std::string name)
	{
		widgets.clear();
	}

	void Gui::update(sf::RenderWindow &window)
	{
		for (auto i = 0; i < widgets.size(); i++)
		{
			widgets[i]->update(window);
		}
	}

	void Gui::draw(sf::RenderWindow &window)
	{
		for (auto i = 0; i < widgets.size(); i++)
		{
			//widgets[i]->update();
			window.draw(*widgets[i]);
		}
	}

	void Gui::removeAll()
	{
		//remove
		//delete window;
	}

	void Gui::setGlobalFont(sf::Font &font)
	{
		m_font = font;
		for (auto i = 0; i < widgets.size(); i++)
		{
			widgets[i]->setFont(m_font);
		}
	}

	void Gui::handleEvents(sf::RenderWindow &window, sf::Event &event)
	{
		for (auto i = 0; i < widgets.size(); i++)
		{
			widgets[i]->handleEvents(window, event);
		}
	}
}