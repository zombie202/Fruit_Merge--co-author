#include "core/Ball.h"


Ball::Ball(float _radius, sf::Vector2f _position) : radius(_radius), position(_position) {}



void Ball::setBallPosition(float new_x, float new_y) 
{
    position = sf::Vector2f(new_x, new_y);
}

void Ball::setBallPosition(sf::Vector2f new_position) 
{
    position = new_position;
}

void Ball::setVelocity(float new_velocity_x, float new_velocity_y) 
{
    velocity = sf::Vector2f(new_velocity_x, new_velocity_y);
}

void Ball::setVelocity(sf::Vector2f new_velocity) 
{
    velocity = new_velocity;
}

void Ball::setRadius(float new_radius) 
{
    radius = new_radius;
}

void Ball::updatePosition(float dt) 
{
    position += velocity * 60.f * dt;
    // position += velocity;
}

sf::Vector2f Ball::nextPosition() 
{
    return position + velocity;
}

bool Ball::operator==(Ball &ball) 
{
    return this->getBallPosition().x == ball.getBallPosition().x && this->getBallPosition().y == ball.getBallPosition().y;
}

void Ball::debugState() const {
    std::cout << "Tile state - Position: (" << position.x << ", " << position.y << "), Velocity: (" << velocity.x << ", " << velocity.y << "), Radius: " << radius << std::endl;
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

sf::Vector2f Ball::getBallPosition() const {
    return position;
}

float Ball::getRadius() const {
    return radius;
}
