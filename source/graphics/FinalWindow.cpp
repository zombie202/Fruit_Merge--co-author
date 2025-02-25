#include "graphics/FinalWindow.h"

// ------------------------------------------------------------------------------------------//
const sf::Color lightBrown(229, 203, 175);
const sf::Color darkBrown(143, 121, 102);
const sf::Color darkerBrown(112, 103, 76);
// ------------------------------------------------------------------------------------------//
const sf::Vector2f windowSize = sf::Vector2f(700, 300);
const sf::Vector2f windowPosition = sf::Vector2f(150, 300);
// ------------------------------------------------------------------------------------------//
const sf::Vector2f backWindowSize = sf::Vector2f(720, 320);
const sf::Vector2f backWindowPosition = sf::Vector2f(135, 285);
// ------------------------------------------------------------------------------------------//
const sf::Vector2f inputBoxSize = sf::Vector2f(600, 80);
// ------------------------------------------------------------------------------------------//
const std::string headerTextText = "Write your nick";
const std::string enterTextText = "ENTER";
const std::string mockUsername = "username";
// ------------------------------------------------------------------------------------------//
const unsigned int headerTextSize = 50;
const unsigned int enterTextSize = 50;
const float outlineThickness = 2;
// ------------------------------------------------------------------------------------------//
const size_t usernameMaxLenght = 20;
// ------------------------------------------------------------------------------------------//

FinalWindow::FinalWindow()
{
    // --------------------------------------------------------------------------------------//
    // Create all of the sprites
    // --------------------------------------------------------------------------------------//
    makeWindow();
    makeBackWindow();
    makeInputBox();
    loadFont();
    makeHeaderText();
    makeEnterText();
    makeUsernameText();
}

void FinalWindow::draw(sf::RenderWindow& mainWindow)
{
    // --------------------------------------------------------------------------------------//
    // Draw everything onto screen
    // arguments: mainWindow - window on which sprites are meant to be drawn on
    // --------------------------------------------------------------------------------------//
    mainWindow.draw(backWindow);
    mainWindow.draw(window);
    mainWindow.draw(inputBox);
    mainWindow.draw(headerText);
    mainWindow.draw(enterText);
    mainWindow.draw(usernameText);
}

void FinalWindow::update(sf::RenderWindow& mainWindow)
{
    // --------------------------------------------------------------------------------------//
    // Gather live information the class need
    // arguments: mainWindow - window from which the intel must be gathered
    // --------------------------------------------------------------------------------------//
    colorHoveredButton(mainWindow);
    getUserInput();
    usernameText.setString(username);
    usernameText.setPosition(getUsernameTextPosition());
}

bool FinalWindow::enterClicked(bool click)
{
    // --------------------------------------------------------------------------------------//
    // Checks if button is being clicked
    // --------------------------------------------------------------------------------------//
    if (enterText.getColor() == sf::Color::Magenta && click)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string FinalWindow::getUsername()
{
    // --------------------------------------------------------------------------------------//
    // return username string
    // --------------------------------------------------------------------------------------//
    return username;
}

void FinalWindow::loadFont()
{
    // --------------------------------------------------------------------------------------//
    // Load font used in text in window
    // --------------------------------------------------------------------------------------//
    if (!font.loadFromFile("assets/kalamBold.ttf"))
    {
        std::cerr << "Unable to load kalamBold font";
    }
}

void FinalWindow::makeWindow()
{
    // --------------------------------------------------------------------------------------//
    // Creates th window
    // --------------------------------------------------------------------------------------//
    window.setSize(windowSize);
    window.setFillColor(lightBrown);
    window.setPosition(windowPosition);
}

void FinalWindow::makeBackWindow()
{
    // --------------------------------------------------------------------------------------//
    // Adds "depth" to window
    // --------------------------------------------------------------------------------------//
    backWindow.setSize(backWindowSize);
    backWindow.setFillColor(darkBrown);
    backWindow.setPosition(backWindowPosition);
}

void FinalWindow::makeInputBox()
{
    // --------------------------------------------------------------------------------------//
    // Creates input box
    // --------------------------------------------------------------------------------------//
    inputBox.setSize(inputBoxSize);
    inputBox.setFillColor(darkerBrown);
    inputBox.setPosition(getInputBoxPosition());
}

void FinalWindow::makeHeaderText()
{
    // --------------------------------------------------------------------------------------//
    // Creates header text
    // --------------------------------------------------------------------------------------//
    headerText.setString(headerTextText);
    headerText.setFont(font);
    headerText.setOutlineColor(sf::Color::Black);
    headerText.setOutlineThickness(outlineThickness);
    headerText.setCharacterSize(headerTextSize);
    headerText.setPosition(getHeaderTextPosition());
}

void FinalWindow::makeEnterText()
{
    // --------------------------------------------------------------------------------------//
    // Creates "ENTER" text
    // --------------------------------------------------------------------------------------//
    enterText.setString(enterTextText);
    enterText.setFont(font);
    enterText.setOutlineColor(sf::Color::Black);
    enterText.setOutlineThickness(outlineThickness);
    enterText.setCharacterSize(enterTextSize);
    enterText.setPosition(getEnterTextPosition());
}

void FinalWindow::makeUsernameText()
{
    // --------------------------------------------------------------------------------------//
    // Creates username text in input box
    // --------------------------------------------------------------------------------------//
    usernameText.setString(username);
    usernameText.setFont(font);
    usernameText.setOutlineColor(sf::Color::Black);
    usernameText.setOutlineThickness(outlineThickness);
    usernameText.setCharacterSize(inputBox.getGlobalBounds().height / 2);
    usernameText.setPosition(getUsernameTextPosition());
}

sf::Vector2f FinalWindow::getInputBoxPosition()
{
    // --------------------------------------------------------------------------------------//
    // Positions input box in the middle of the window
    // --------------------------------------------------------------------------------------//
    int xPosition = window.getPosition().x + (window.getSize().x - inputBox.getLocalBounds().width) / 2;
    int yPosition = window.getPosition().y + (window.getSize().y - inputBox.getLocalBounds().height) / 2;
    return sf::Vector2f(xPosition, yPosition);
}

sf::Vector2f FinalWindow::getHeaderTextPosition()
{
    // --------------------------------------------------------------------------------------//
    // Positions header in the middle and in the upper part of window
    // --------------------------------------------------------------------------------------//
    int xPosition = window.getPosition().x + (window.getSize().x - headerText.getLocalBounds().width) / 2;
    int yPosition = window.getPosition().y + (window.getSize().y - headerText.getLocalBounds().height) / 20;
    return sf::Vector2f(xPosition, yPosition);
}

sf::Vector2f FinalWindow::getEnterTextPosition()
{
    // --------------------------------------------------------------------------------------//
    // Positions "enter" button in the middle and in the down part of window
    // --------------------------------------------------------------------------------------//
    int xPosition = window.getPosition().x + (window.getSize().x - enterText.getLocalBounds().width) / 2;
    int yPosition = window.getPosition().y + window.getSize().y - enterText.getLocalBounds().height * 2;
    return sf::Vector2f(xPosition, yPosition);
}

sf::Vector2f FinalWindow::getUsernameTextPosition()
{
    // --------------------------------------------------------------------------------------//
    // Positions username in the middle of the input box
    // --------------------------------------------------------------------------------------//
    int xPosition = inputBox.getPosition().x + (inputBox.getGlobalBounds().width - usernameText.getGlobalBounds().width)/2;
    int yPosition = inputBox.getPosition().y + (inputBox.getGlobalBounds().height - usernameText.getGlobalBounds().height) / 4;
    return sf::Vector2f(xPosition, yPosition);
}

void FinalWindow::colorHoveredButton(sf::RenderWindow& mainWindow)
{
    // --------------------------------------------------------------------------------------//
    // Checks for mouse position in the window and colors buttons if mouse is over them
    // arguments: mainWindow - window in which the mouse is located
    // --------------------------------------------------------------------------------------//
    float mouseX = static_cast<float>(sf::Mouse::getPosition(mainWindow).x);
    float mouseY = static_cast<float>(sf::Mouse::getPosition(mainWindow).y);
    sf::Vector2 mousePosition = sf::Vector2(mouseX, mouseY);
    // Color the "ENTER" button
    if (enterText.getGlobalBounds().contains(mousePosition))
    {
        enterText.setFillColor(sf::Color::Magenta);
    }
    else
    {
        enterText.setFillColor(sf::Color::White);
    }
}

void FinalWindow::getUserInput()
{
    // --------------------------------------------------------------------------------------//
    // Gets input from EventHandler class and adds characters into username string,
    // also substuckt if backspace is clicked
    // --------------------------------------------------------------------------------------//
    if (EventHandler::newCharacter && username.size() < usernameMaxLenght)
    {
        username.push_back(static_cast<char>(EventHandler::character));
    }
    if (EventHandler::backspaceClicked && username.size() > 0)
    {
        username.erase(username.size() - 1, 1);
    }
}
