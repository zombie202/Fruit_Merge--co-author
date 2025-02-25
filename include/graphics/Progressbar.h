#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Progressbar
{
    private:
        const std::string texturePath = "assets/Progressbarr.png";
        sf::Texture barTexture;
        bool loadTexture(const std::string& _texturePath);
        sf::RectangleShape bar;
        float fill = 50.f;
        const int height = 50;
        const int width = 300;
        sf::Sprite frame;

    public:
        Progressbar();
        void setFill(float fill);
        void setPosition(sf::Vector2f position);
        void draw(sf::RenderWindow& window);
};