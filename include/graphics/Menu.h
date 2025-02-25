#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
private:
	sf::Font font;							//		Czcionka
	sf::Texture menuBackground;				//		Tekstura t�a
	sf::Texture instructionBackground;		//		Tekstura t�a w miejscu instrukcji
	static sf::Sprite instBackground;		//		Sprite w miejscu instrukcji
	static sf::Sprite background;			//		Sprite naszego t�a
	int selectedItem;						//		Wybrany element menu

public:
	Menu();		//		Konstruktor

	//	Te dwa gettery poni�ej s� statyczne, aby mo�liwe by�o ich
	//	u�ycie w pliku UiManager.cpp dla metod runMenu() i runInstruction()
	float width = 1000;													//		Domy�lna szeroko�� menu
	float height = 1000;												//		Domy�lna wysoko�� menu
	static sf::Sprite getInstBackground() { return instBackground; }	//		Statyczny getter dla spritu instrukcji
	static sf::Sprite getBackground() { return background; }			//		Statyczny getter dla spritu g��wnego menu
	std::vector<sf::Text> menuItems;									//		Elementy menu
	void drawMainMenu(sf::RenderWindow& window);						//		Wy�wietlanie g��wnego menu
	void drawInstruction(sf::RenderWindow& window);						//		Wy�wietlanie instrukcji gry
	bool IsMouseOver(sf::RenderWindow& window, int index);				//		Sprawdzenie, czy myszka jest nad przyciskiem
};
#endif
