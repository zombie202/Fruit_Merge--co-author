#include "graphics/ExitWindow.h"

// ------------------------------------------------------------------------------------------//
const sf::Color lightBrown(229, 203, 175);
const sf::Color darkBrown(143, 121, 102);
// ------------------------------------------------------------------------------------------//
const sf::Vector2f windowSize = sf::Vector2f(700, 300);
const sf::Vector2f windowPosition = sf::Vector2f(150, 300);
// ------------------------------------------------------------------------------------------//
const sf::Vector2f backWindowSize = sf::Vector2f(720, 320);
const sf::Vector2f backWindowPosition = sf::Vector2f(135, 285);
// ------------------------------------------------------------------------------------------//
const std::string headerTextText = "Do you want to leave?";
const std::string yesTextText = "YES";
const std::string noTextText = "NO";
// ------------------------------------------------------------------------------------------//
const unsigned int headerTextSize = 50;
const unsigned int optionTextSize = 70;
const float outlineThicknes = 2;
// ------------------------------------------------------------------------------------------//

ExitWindow::ExitWindow()
{
	// --------------------------------------------------------------------------------------//
	// Create all of the sprites
	// --------------------------------------------------------------------------------------//
	makeWindow();
	makeBackWindow();
	loadFont();
	makeHeaderText();
	makeYesText();
	makeNoText();
}

void ExitWindow::draw(sf::RenderWindow& mainWindow)
{
	// --------------------------------------------------------------------------------------//
	// Draw everything onto screen
	// arguments: mainWindow - window on which sprites are meant to be drawn on
	// --------------------------------------------------------------------------------------//
	mainWindow.draw(backWindow);
	mainWindow.draw(window);
	mainWindow.draw(headerText);
	mainWindow.draw(yesText);
	mainWindow.draw(noText);
}

void ExitWindow::update(sf::RenderWindow& mainWindow)
{
	// --------------------------------------------------------------------------------------//
	// Gather live information the class need
	// arguments: mainWindow - window from which the intel must be gathered
	// --------------------------------------------------------------------------------------//
	colorHoveredButton(mainWindow);
}

bool ExitWindow::yesClicked(bool click)
{
	// --------------------------------------------------------------------------------------//
	// Checks if button is being clicked
	// --------------------------------------------------------------------------------------//
	if (yesText.getColor() == sf::Color::Magenta && click)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool ExitWindow::noClicked(bool click)
{
	// --------------------------------------------------------------------------------------//
	// Checks if button is being clicked
	// --------------------------------------------------------------------------------------//
	if (noText.getColor() == sf::Color::Magenta && click)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ExitWindow::loadFont()
{
	// --------------------------------------------------------------------------------------//
	// Load font used for text in window
	// --------------------------------------------------------------------------------------//
	if (!font.loadFromFile("assets/kalamBold.ttf"))
	{
		std::cerr << "Unable to load kalamBold font";
	}
}

void ExitWindow::makeWindow()
{
	// --------------------------------------------------------------------------------------//
	// Creates the window
	// --------------------------------------------------------------------------------------//
	window.setSize(windowSize);
	window.setFillColor(lightBrown);
	window.setPosition(windowPosition);
}

void ExitWindow::makeBackWindow()
{
	// --------------------------------------------------------------------------------------//
	// Adds depth to the window
	// --------------------------------------------------------------------------------------//
	backWindow.setSize(backWindowSize);
	backWindow.setFillColor(darkBrown);
	backWindow.setPosition(backWindowPosition);
}

void ExitWindow::makeHeaderText()
{
	// --------------------------------------------------------------------------------------//
	// Creates "Do you want to leave text"
	// --------------------------------------------------------------------------------------//
	headerText.setString(headerTextText);
	headerText.setFont(font);
	headerText.setOutlineColor(sf::Color::Black);
	headerText.setOutlineThickness(outlineThicknes);
	headerText.setCharacterSize(headerTextSize);
	headerText.setPosition(getHeaderTextPosition());
}

void ExitWindow::makeYesText()
{
	// --------------------------------------------------------------------------------------//
	// Creates "YES" button
	// --------------------------------------------------------------------------------------//
	yesText.setString(yesTextText);
	yesText.setFont(font);
	yesText.setOutlineColor(sf::Color::Black);
	yesText.setOutlineThickness(outlineThicknes);
	yesText.setCharacterSize(optionTextSize);
	yesText.setPosition(getYesTextPosition());
}

void ExitWindow::makeNoText()
{
	// --------------------------------------------------------------------------------------//
	// Creates "NO" button
	// --------------------------------------------------------------------------------------//
	noText.setString(noTextText);
	noText.setFont(font);
	noText.setOutlineColor(sf::Color::Black);
	noText.setOutlineThickness(outlineThicknes);
	noText.setCharacterSize(optionTextSize);
	noText.setPosition(getNoTextPosition());
}

sf::Vector2f ExitWindow::getHeaderTextPosition()
{
	// --------------------------------------------------------------------------------------//
	// Positions header in the middle of the window and near upper side
	// --------------------------------------------------------------------------------------//
	int xPosition = window.getPosition().x + (window.getSize().x - headerText.getLocalBounds().width) / 2;
	int yPosition = window.getPosition().y + (window.getSize().y - headerText.getLocalBounds().height) / 8;
	return sf::Vector2f(xPosition, yPosition);
}

sf::Vector2f ExitWindow::getYesTextPosition()
{
	// --------------------------------------------------------------------------------------//
	// Positions "YES" button
	// --------------------------------------------------------------------------------------//
	int xPosition = headerText.getPosition().x;
	int yPosition = window.getPosition().y + window.getSize().y - yesText.getLocalBounds().height * 2.5;
	return sf::Vector2f(xPosition, yPosition);
}

sf::Vector2f ExitWindow::getNoTextPosition()
{
	// --------------------------------------------------------------------------------------//
	// Positions "NO" button
	// --------------------------------------------------------------------------------------//
	int xPosition = headerText.getPosition().x + headerText.getLocalBounds().width - noText.getLocalBounds().width;
	int yPosition = window.getPosition().y + window.getSize().y - noText.getLocalBounds().height * 2.5;
	return sf::Vector2f(xPosition, yPosition);
}

void ExitWindow::colorHoveredButton(sf::RenderWindow& mainWindow)
{
	// --------------------------------------------------------------------------------------//
	// Checks for mouse position in the window and colors buttons if mouse is over them
	// arguments: mainWindow - window in which the mouse is located
	// --------------------------------------------------------------------------------------//
	float mouseX = static_cast<float>(sf::Mouse::getPosition(mainWindow).x);
	float mouseY = static_cast<float>(sf::Mouse::getPosition(mainWindow).y);
	sf::Vector2 mousePosition = sf::Vector2(mouseX, mouseY);
	// Color the "YES" button
	if (yesText.getGlobalBounds().contains(mousePosition))
	{
		yesText.setFillColor(sf::Color::Magenta);
	}
	else
	{
		yesText.setFillColor(sf::Color::White);
	}
	// --------------------------------------------------------------------------------------//
	// Color the "NO" button
	if (noText.getGlobalBounds().contains(mousePosition))
	{
		noText.setFillColor(sf::Color::Magenta);
	}
	else
	{
		noText.setFillColor(sf::Color::White);
	}
}
