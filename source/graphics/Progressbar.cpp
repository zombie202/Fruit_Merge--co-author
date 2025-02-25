#include "graphics/Progressbar.h"


Progressbar::Progressbar()
{
    if (!loadTexture(texturePath)) {
        std::cerr << "Error loading texture: " << texturePath << std::endl;
    } else {
        std::cout << "Texture loaded successfully: " << texturePath << std::endl;
    }
    bar.setFillColor(sf::Color(219, 107, 92));
}

void Progressbar::setFill(float fill)
{   
    int x = 7 + (286 * fill) * 0.01;
    sf::Vector2f newSize(x, 50);
    bar.setSize(newSize);
}

bool Progressbar::loadTexture(const std::string& texturePath)
{
    if (!barTexture.loadFromFile(texturePath)) {
        return false;
    }
    frame.setTexture(barTexture);
    return true;
}

void Progressbar::setPosition(sf::Vector2f position)
{
    frame.setPosition(position);
    bar.setPosition(position);
}

void Progressbar::draw(sf::RenderWindow& window)
{
    window.draw(bar);
    window.draw(frame);
}