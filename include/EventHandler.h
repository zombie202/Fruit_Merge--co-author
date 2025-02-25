#pragma once
#include "SFML/Graphics.hpp"

class EventHandler
{
private:
	static bool isReleased;
public:
	static bool leftMouseButtonClicked;
	static bool rightMouseButtonClicked;
	static bool escapeClicked;
	static char character;
	static bool newCharacter;
	static bool backspaceClicked;

public:
	static void handleEvent(sf::RenderWindow& window);
	static void resetVariables();
};