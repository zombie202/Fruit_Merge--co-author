#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

class Cloud : public sf::Sprite
{
    private:
        const std::string texturePath = "assets/cloud.png";
        bool loadTexture(const std::string& _texturePath);
        sf::Texture cloudTexture;
        const int width = 155; // szerokość chmurki
        const int height = 97; // wysokośc chmurki

    public:
        Cloud();

        //gettery
        int getHeight() const { return height; };
        int getWidth() const { return width; };

        //Ustawia pozycję chmury na podstawie porządanej pozycji środkowej
        void setCloudPosition(sf::Vector2f middlePosition);
};