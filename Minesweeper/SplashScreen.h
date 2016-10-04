#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
class SplashScreen
{
public:
	SplashScreen();
	~SplashScreen();

	void Create(unsigned char opacity, float time);
private:
	bool setTransparent(HWND hWnd, const sf::Image& image, unsigned char alpha);

	sf::Image		 img;
	sf::Texture		 texture;
	sf::Sprite	     sprite;
	sf::RenderWindow window;

	sf::Time		 deltaTime, elapsedTime;
	sf::Clock		 clock;
};

#endif