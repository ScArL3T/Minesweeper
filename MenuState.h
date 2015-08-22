#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "StateManager.h"

class MenuState : public State
{
public:
	~MenuState();
	void init(sf::RenderWindow &window) override;
	void update(sf::RenderWindow &window, float dt) override;
	void draw(sf::RenderWindow &window) override;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override;
private:
	//Static functions for buttons
	static void onHover();
	static void onClick();

	//Float needed for setPosition(sf::Vector2f)
	float WIDTH, HEIGHT;
	bool  playState;

	sf::Text		   m_title;  //Menu title
	sf::RectangleShape m_backgr; //Menu background

	sf::Texture m_panelTexture;  //Menu panel texture
	sf::Sprite  m_panelSprite;   //Menu panel sprite

	//Custom GUI
	gui::Gui		  gui;
	gui::Button::Ptr  playButton, quitButton; 
};

#endif