#include "graphics/Cloud.h"

Cloud::Cloud() : sf::Sprite()
{
    if (!loadTexture(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    } else {
        std::cout << "Texture loaded successfully: " << texturePath << std::endl;
    }
}

bool Cloud::loadTexture(const std::string& texturePath)
{
    if (!cloudTexture.loadFromFile(texturePath)) {
        return false;
    }
    this->setTexture(cloudTexture);
    return true;
}

void Cloud::setCloudPosition(sf::Vector2f middlePosition)
{
    setPosition(middlePosition.x - width / 2, middlePosition.y - height / 2);
}
