#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "StateManager.h"

class MenuState : public State
{
public:
	void init(sf::RenderWindow &window) override;
	void update(sf::RenderWindow &window, float dt) override;
	void draw(sf::RenderWindow &window) override;
	void handleEvents(sf::RenderWindow &window, sf::Event &event) override;
	void destroy(sf::RenderWindow &window) override;

private:
	static void onHover();
	static void onClick();

	//Float needed for setPosition(sf::Vector2f)
	float WIDTH, HEIGHT;
	bool  playState;

	sf::Text		   m_title;
	sf::RectangleShape m_backgr;

	gui::Gui		  gui;
	gui::Button::Ptr  playButton, quitButton; 

	sf::Texture m_panelTexture;
	sf::Sprite  m_panelSprite;
};

#endif