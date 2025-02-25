#pragma once

#include "core/Ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

enum FruitType
{
    Apple = 49,
    Appricot = 43,
    Blueberry = 18,
    Coconut = 95,
    Melon = 80,
    Pineapple = 122,
    Pumpkin = 62,
    Strawberry = 23
};

class Fruit : public Ball, public sf::Sprite
{
public:
    Fruit(const sf::Vector2f& position, FruitType type);
    void synchronizePosition();
    FruitType getFruitType() const;

private:
    FruitType type;
    bool loadTexture(const std::string& texturePath);
    sf::Texture fruitTexture;
    // sf::Sprite appleSprite;
    float fruitRadius; // Stała wartość promienia jabłka
};