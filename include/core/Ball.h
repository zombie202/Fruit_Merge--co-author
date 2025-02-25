#ifndef BALL_H
#define BALL_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "Physics.h"
#include <iostream>


enum boundSide {
    left,
    right,
    up,
    down,
    none
};

class Ball {
private:
    sf::Vector2f position;  // aktualna pozycja środka kulki na planszy
    sf::Vector2f velocity;  // prędkość kulki w pixelach na klatkę trwającą 1/60s
    float radius;           // promień kulki
    std::string texturePath;

public:
    Ball(sf::Vector2f _position);
    Ball(float _radius, sf::Vector2f _position);
    Ball(const std::string& texturePath, int points, const sf::Vector2f& position);

    void setBallPosition(float new_x, float new_y);
    void setBallPosition(sf::Vector2f new_position);
    void setVelocity(float new_velocity_x, float new_velocity_y);
    void setVelocity(sf::Vector2f new_velocity);
    void setRadius(float new_radius);
    void updatePosition(float dt);
    sf::Vector2f nextPosition();
    bool operator==(Ball &ball);
    void debugState() const;

    sf::Vector2f getVelocity() const;
    sf::Vector2f getBallPosition() const;
    float getRadius() const;
};

#endif
