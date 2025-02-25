#include "graphics/Menu.h"
#include <iostream>

//	Konstruktor klasy Menu w pełnej krasie
Menu::Menu() {

	//	Czcionka do menu
	if (!font.loadFromFile("assets/kalamBold.ttf"))
	{
		std::cout << "Nie można załadować czcionki! " << std::endl;
	}

	//	Tło do menu głównego
	if (!menuBackground.loadFromFile("assets/menuBackground.png"))
	{
		std::cout << "Nie można załadować tła! " << std::endl;
	}
	else {
		background.setTexture(menuBackground);
		background.setScale(width / menuBackground.getSize().x, height / menuBackground.getSize().y);
	}
	//	Dodano grafikę aboutGame.png do konstruktora Menu
	if (!instructionBackground.loadFromFile("assets/aboutGame.png"))
	{
		std::cout << "Nie można załadować tła! " << std::endl;
	}
	else
	{
		instBackground.setTexture(instructionBackground);
		instBackground.setScale(width / instructionBackground.getSize().x, height / instructionBackground.getSize().y);
	}

	//	Przysk Play prowadzący do rozgrywki
	sf::Text startGame;
	startGame.setFont(font);
	startGame.setFillColor(sf::Color::Magenta);
	startGame.setString("Play");
	startGame.setPosition(sf::Vector2f(width / 2.15, height / 1.70));
	menuItems.push_back(startGame);

	//	Przycisk About... prowadzący do instrukcji
	sf::Text aboutGame;
	aboutGame.setFont(font);
	aboutGame.setFillColor(sf::Color::White);
	aboutGame.setString("About...");
	aboutGame.setPosition(sf::Vector2f(width / 2.2, height / 1.43));
	menuItems.push_back(aboutGame);

	//	Przycisk Exit
	sf::Text quitGame;
	quitGame.setFont(font);
	quitGame.setFillColor(sf::Color::White);
	quitGame.setString("Exit");
	quitGame.setPosition(sf::Vector2f(width / 2.15, height / 1.23));
	menuItems.push_back(quitGame);

	//	Opis gry jako string
	sf::Text descriptionGame;
	descriptionGame.setFont(font);
	descriptionGame.setFillColor(sf::Color::White);
	descriptionGame.setString("This game is very simple. These are the rules: \n\n1. Select with the mouse the point from\n which you want to drop the fruit.\n2. Click left button, if you want to drop a fruit.\n3. You can drop these fruits until they reach\n the top edge of the box.\n4. Your task is achieve as much points\n as you can!");
	descriptionGame.setPosition(sf::Vector2f(width / 4.5, height / 3.1));
	menuItems.push_back(descriptionGame);

	//	Dodany przycisk "Back", dzięki czemu można się cofnąć z opisu, z powrotem do menu
	sf::Text back;
	back.setFont(font);
	back.setFillColor(sf::Color::White);
	back.setString("Back");
	back.setPosition(sf::Vector2f(width / 2.15, height / 1.15));
	menuItems.push_back(back);

	selectedItem = 0;
}

//	Metoda, która pozwala nam wyświetlić elementy instrukcji
void Menu::drawInstruction(sf::RenderWindow& window)
{
	window.draw(instBackground);
	for (size_t i = 3; i < menuItems.size(); i++)
	{
		window.draw(menuItems[i]);
	}
}

//	Metoda, która pozwala nam wyświetlić elementy głównego menu
void Menu::drawMainMenu(sf::RenderWindow& window)
{
	window.draw(background);
	for (size_t i = 0; i < menuItems.size() - 2; i++)
	{
		window.draw(menuItems[i]);
	}
}

//	Metoda boolowska, która sprawdza, czy myszka znajduje się nad hitboxem
bool Menu::IsMouseOver(sf::RenderWindow& window, int index)
{
	//	Zwiększyłem zakres hitboxów przy menu, aby wygodniej można było wybrać daną opcję
	std::vector<int> hitBoxEdges = { 90, 143, 30 };
	//	Elementy wektora potrzebne do zwiększenia zasięgu widzenia przycisku

	float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
	float mouseY = static_cast<float>(sf::Mouse::getPosition(window).y);

	float btnPosX = menuItems[index].getPosition().x;
	float btnPosY = menuItems[index].getPosition().y;

	float btnxPosWidth = menuItems[index].getGlobalBounds().width;
	float btnyPosHeight = menuItems[index].getGlobalBounds().height;

	//	Odpowiednio skalibrowanie widzenie myszy
	if (index == 4)
	{
		return (mouseX >= btnPosX - btnxPosWidth + hitBoxEdges[2] && mouseX <= btnPosX + btnxPosWidth + hitBoxEdges[2] &&
			mouseY >= btnPosY - btnyPosHeight && mouseY <= btnPosY + btnyPosHeight + hitBoxEdges[2]);
	}
	else {
		return (mouseX >= btnPosX - btnxPosWidth - hitBoxEdges[0] && mouseX <= btnPosX + btnxPosWidth + hitBoxEdges[1] &&
			mouseY >= btnPosY - btnyPosHeight && mouseY <= btnPosY + btnyPosHeight + hitBoxEdges[2]);
	}
}