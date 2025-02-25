#pragma once
#include "SFML/Graphics.hpp"
#include "EventHandler.h"
#include "RankingManager.h"
#include <iostream>

class FinalWindow
{
private:
    sf::RectangleShape window;
    sf::RectangleShape backWindow;
    sf::RectangleShape inputBox;
    sf::Font font;
    sf::Text headerText;
    sf::Text enterText;
    sf::Text usernameText;
    std::string username;

public:
    FinalWindow();                                          // initialize all the sprites and load font
    // -------------------------------------------------------------------------------------------------------------------//
    void draw(sf::RenderWindow& mainWindow);                // draw window onto screen
    void update(sf::RenderWindow& mainWindow);              // update the information window receive
    // -------------------------------------------------------------------------------------------------------------------//
    bool enterClicked(bool click);                          // return true if button is cklicked
    // -------------------------------------------------------------------------------------------------------------------//
    std::string getUsername();                              // return username
    // -------------------------------------------------------------------------------------------------------------------//
private:
    void loadFont();                                        //
    void makeWindow();                                      // 
    void makeBackWindow();                                  // inicjalization functions,
    void makeInputBox();                                    // for contructor to not be
    void makeHeaderText();                                  // to big
    void makeEnterText();                                   // 
    void makeUsernameText();                                // 
    // -------------------------------------------------------------------------------------------------------------------//
    sf::Vector2f getInputBoxPosition();                     // 
    sf::Vector2f getHeaderTextPosition();                   // more acurate positioning
    sf::Vector2f getEnterTextPosition();                    // than "random" numbers
    sf::Vector2f getUsernameTextPosition();                 // 
    // -------------------------------------------------------------------------------------------------------------------//
    void colorHoveredButton(sf::RenderWindow& mainWindow);  // checks if mouse is over a button and color it acordingly
    // -------------------------------------------------------------------------------------------------------------------//
    void getUserInput();                                    // takes user input and updates the username string
};