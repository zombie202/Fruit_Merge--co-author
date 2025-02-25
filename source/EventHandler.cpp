#include "EventHandler.h"
#include <iostream>

bool EventHandler::leftMouseButtonClicked = false;
bool EventHandler::rightMouseButtonClicked = false;
bool EventHandler::isReleased = true;
bool EventHandler::escapeClicked = false;
bool EventHandler::newCharacter = false;
bool EventHandler::backspaceClicked = false;
char EventHandler::character;

void EventHandler::handleEvent(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            EventHandler::escapeClicked = true;
        }
        if (event.type == sf::Event::LostFocus)
        {
            break;
        }
        if (event.type == sf::Event::TextEntered)
        {
            if (event.text.unicode == '\b')
            {
                EventHandler::backspaceClicked = true;
            }
            else if (event.text.unicode < 128)
            {
                EventHandler::character = static_cast<char>(event.text.unicode);
                EventHandler::newCharacter = true;
            }
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.scancode == sf::Keyboard::Scan::Escape && !EventHandler::escapeClicked)
            {
                EventHandler::escapeClicked = true;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right && EventHandler::isReleased)
            {
                EventHandler::rightMouseButtonClicked = true;
                EventHandler::isReleased = false;
            }
            if (event.mouseButton.button == sf::Mouse::Left && EventHandler::isReleased)
            {
                EventHandler::leftMouseButtonClicked = true;
                EventHandler::isReleased = false;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                EventHandler::isReleased = true;
            }
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                EventHandler::isReleased = true;
            }
        }
    }
}


void EventHandler::resetVariables()
{
    EventHandler::leftMouseButtonClicked = false;
    EventHandler::rightMouseButtonClicked = false;
    EventHandler::newCharacter = false;
    EventHandler::backspaceClicked = false;
}