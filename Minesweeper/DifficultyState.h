#ifndef DIFFICULTYSTATE_H
#define DIFFICULTYSTATE_H

#include "StateManager.h"

class DifficultyState: public State
{
public:
	~DifficultyState();
	void init(sf::RenderWindow &window)							  override final;
	void update(sf::RenderWindow &window, float dt)				  override final;
	void draw(sf::RenderWindow &window)							  override final;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override final;
private:
	//Static functions for buttons
	static void onHover();
	static void onClick();

	//Float needed for setPosition(sf::Vector2f)
	float WIDTH, HEIGHT;

	sf::RectangleShape m_backgr; //Menu background

	//Custom GUI
	gui::Gui		  gui;
	gui::Button::Ptr  easyButton, intermButton, hardButton;
};

#endif