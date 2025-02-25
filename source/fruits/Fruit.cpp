#include "fruits/Fruit.h"

// Konstruktor klasy Fruit
Fruit::Fruit(const sf::Vector2f& _position, FruitType type) 
    : Ball(static_cast<float>(type), _position), sf::Sprite(), type(type) // Przekazanie promienia i pozycji do konstruktora klasy bazowej
{
    // setRadius(static_cast<float>(type));
    std::string texturePath;
    switch (type) {
    case FruitType::Apple:
        texturePath = "assets/" + std::string("apple.png");
        break;
    case FruitType::Appricot:
        texturePath = "assets/" + std::string("apricot.png");
        break;
    case FruitType::Blueberry:
        texturePath = "assets/" + std::string("blueberry.png");
        break;
    case FruitType::Coconut:
        texturePath = "assets/" + std::string("coconut.png");
        break;
    case FruitType::Melon:
        texturePath = "assets/" + std::string("melon.png");
        break;
    case FruitType::Pineapple:
        texturePath = "assets/" + std::string("pineapple.png");
        break;
    case FruitType::Pumpkin:
        texturePath = "assets/" + std::string("pumpkin.png");
        break;
    case FruitType::Strawberry:
        texturePath = "assets/" + std::string("strawberry.png");
        break;
    }
    if (!loadTexture(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    } else {
        std::cout << "Texture loaded successfully: " << texturePath << std::endl;
    }
}

// Metoda do ładowania tekstury
bool Fruit::loadTexture(const std::string& _texturePath) {
    if (!fruitTexture.loadFromFile(_texturePath)) {
        return false;
    }
    this->setTexture(fruitTexture);
    return true;
}

void Fruit::synchronizePosition()
{
    float xPosition = getBallPosition().x - getRadius();
    float yPosition = getBallPosition().y - getRadius();
    setPosition(sf::Vector2f(xPosition, yPosition));
}

FruitType Fruit::getFruitType() const
{
    return type;
}