#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
private:
	sf::Font font;							//		Czcionka
	sf::Texture menuBackground;				//		Tekstura t³a
	sf::Texture instructionBackground;		//		Tekstura t³a w miejscu instrukcji
	static sf::Sprite instBackground;		//		Sprite w miejscu instrukcji
	static sf::Sprite background;			//		Sprite naszego t³a
	int selectedItem;						//		Wybrany element menu

public:
	Menu();		//		Konstruktor

	//	Te dwa gettery poni¿ej s¹ statyczne, aby mo¿liwe by³o ich
	//	u¿ycie w pliku UiManager.cpp dla metod runMenu() i runInstruction()
	float width = 1000;													//		Domyœlna szerokoœæ menu
	float height = 1000;												//		Domyœlna wysokoœæ menu
	static sf::Sprite getInstBackground() { return instBackground; }	//		Statyczny getter dla spritu instrukcji
	static sf::Sprite getBackground() { return background; }			//		Statyczny getter dla spritu g³ównego menu
	std::vector<sf::Text> menuItems;									//		Elementy menu
	void drawMainMenu(sf::RenderWindow& window);						//		Wyœwietlanie g³ównego menu
	void drawInstruction(sf::RenderWindow& window);						//		Wyœwietlanie instrukcji gry
	bool IsMouseOver(sf::RenderWindow& window, int index);				//		Sprawdzenie, czy myszka jest nad przyciskiem
};
#endif
