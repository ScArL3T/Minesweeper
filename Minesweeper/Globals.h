#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gui.h"
#include "Button.h"
#include <iostream>
#include <memory>
#include <functional>

enum class Difficulty
{
	Easy = 0,
	Intermediate,
	Hard
};

extern Difficulty m_difficulty;

const unsigned int FPS = 60;

extern sf::Font  font;
extern sf::Sound clickSound;
extern sf::Sound hoverSound;

#endif