#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

class ExitWindow
{
private:
	sf::RectangleShape window;
	sf::RectangleShape backWindow;
	sf::Font font;
	sf::Text headerText;
	sf::Text yesText;
	sf::Text noText;

public:
	ExitWindow();											// initialize all the sprites and load font
	// -------------------------------------------------------------------------------------------------------------------//
	void draw(sf::RenderWindow& mainWindow);				// draw window onto screen
	void update(sf::RenderWindow& mainWindow);				// update the information window receive
	// -------------------------------------------------------------------------------------------------------------------//
	bool yesClicked(bool click);							// returns true if
	bool noClicked(bool click);								// button is clicked
	// -------------------------------------------------------------------------------------------------------------------//
private:
	void loadFont();										// 
	void makeWindow();										// inicjalization
	void makeBackWindow();									// functions, for
	void makeHeaderText();									// constructor not
	void makeYesText();										// to be to big
	void makeNoText();										// 
	// -------------------------------------------------------------------------------------------------------------------//
	sf::Vector2f getHeaderTextPosition();					// More acurate
	sf::Vector2f getYesTextPosition();						// positioning than
	sf::Vector2f getNoTextPosition();						// "random" numbers
	// -------------------------------------------------------------------------------------------------------------------//
	void colorHoveredButton(sf::RenderWindow& mainWindow);	//checks if mouse is over a button and color it acordingly
};
