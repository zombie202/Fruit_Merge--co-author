#include "core/Board.h"
#include <math.h>
#include <iostream>

Board::Board(sf::Vector2f _boardSize) : boardSize(_boardSize) {}  // Zmiana nazwy argumentu, aby była spójna z deklaracją

void Board::addBall(std::unique_ptr<Fruit> ball) {
    balls.push_back(std::move(ball));
}

void Board::removeBall(std::unique_ptr<Fruit> ball)
{
    balls.erase(balls.begin());
}

void Board::updatePosition(float deltaTime)
{
    for (auto& ball : balls)
    {

        ball->updatePosition(deltaTime);
        // ball->setVelocity((ball->getVelocity() * airResistance));
        ball->setVelocity((ball->getVelocity() + gravity));

    }
}

void Board::bounce() 
{
    //dla każdej kulki zmienia odpowiednio prędkości oraz pozycje w zależności od ściany z którą piłka ma kontakt
    for (auto& ball : balls)
    {
        //auto side = ball->checkBoundaries(boardSize);
        if (ball->getBallPosition().x > boardSize.x - ball->getRadius())
        {
            ball->setVelocity(-viscosity * (ball->getVelocity().x), friction * ball->getVelocity().y);
            ball->setBallPosition(boardSize.x - ball->getRadius(), ball->getBallPosition().y);
        }
        else if (ball->getBallPosition().x - ball->getRadius() < 0)
        {    
            ball->setVelocity(-viscosity * (ball->getVelocity().x), friction * ball->getVelocity().y);
            ball->setBallPosition(0.f + ball->getRadius(), ball->getBallPosition().y);
        }
        if (ball->getBallPosition().y + ball->getRadius() > boardSize.y)
        {
            ball->setVelocity(friction * ball->getVelocity().x, -viscosity * (ball->getVelocity().y));
            ball->setBallPosition(ball->getBallPosition().x, boardSize.y - ball->getRadius());
        }
    }
}

void Board::otherBallsBounce() {
    for (size_t i = 0; i < balls.size(); i++) {
        for (size_t j = i + 1; j < balls.size(); j++) {
            auto& ballA = balls[i];
            auto& ballB = balls[j];
            if (!(ballA == ballB)) {

                //obliczanie odległości między środkami kulek, osobno dla każdej współrzędnej
                double deltaY = ballA->getBallPosition().y - ballB->getBallPosition().y;
                double deltaX = ballA->getBallPosition().x - ballB->getBallPosition().x;

                //obliczanie odległości między środkami kulek
                double deltaR = deltaX*deltaX + deltaY*deltaY;
                double distance = sqrt(deltaR);

                //sprawdzanie czy kulki się z sobą nakładają
                if (distance <= (ballA->getRadius() + ballB->getRadius())) {

                    //dodatkowe uaktualnienie pozycji kulek (niezależne od ich prędkości), w celu uniemożliwienia ich nakładania się
                    double radiusSum = ballA->getRadius() + ballB->getRadius();

                    //obliczanie nałożenia
                    double correctionX = (radiusSum - distance) * (deltaX/distance);
                    double correctionY = (radiusSum - distance) * (deltaY/distance);

                    //obliczanie proporcji między promieniami
                    double proportionA = ballB->getRadius() / (ballA->getRadius() + ballB->getRadius());
                    double proportionB = ballB->getRadius() / (ballA->getRadius() + ballB->getRadius());

                    //obliczanie przesunięć
                    double correctionAX = (correctionX * proportionA);
                    double correctionAY = (correctionY * proportionA);
                    double correctionBX = -(correctionX * proportionB);
                    double correctionBY = -(correctionY * proportionB);

                    //obliczanie składowych wektorów prędkości zgodnie z zasadami zachowania pędu dla zderzeń sprężystych
                    double velocityAX = ((ballB->getVelocity().x * deltaX + ballB->getVelocity().y * deltaY) * deltaX + (ballA->getVelocity().x * deltaY - ballA->getVelocity().y * deltaX) * deltaY) / deltaR;
                    double velocityAY = ((ballB->getVelocity().x * deltaX + ballB->getVelocity().y * deltaY) * deltaY - (ballA->getVelocity().x * deltaY - ballA->getVelocity().y * deltaX) * deltaX) / deltaR;
                    double velocityBx = ((ballA->getVelocity().x * deltaX + ballA->getVelocity().y * deltaY) * deltaX + (ballB->getVelocity().x * deltaY - ballB->getVelocity().y * deltaX) * deltaY) / deltaR;
                    double velocityBY = ((ballA->getVelocity().x * deltaX + ballA->getVelocity().y * deltaY) * deltaY - (ballB->getVelocity().x * deltaY - ballB->getVelocity().y * deltaX) * deltaX) / deltaR;

                    

                    //ustawienie wektorów prędkości po wyliczeniu ich składowych 
                    ballA->setVelocity(velocityAX, velocityAY);
                    ballB->setVelocity(velocityBx, velocityBY);

                    ballA->setBallPosition(ballA->getBallPosition().x + correctionAX, ballA->getBallPosition().y + correctionAY);
                    ballB->setBallPosition(ballB->getBallPosition().x + correctionBX, ballB->getBallPosition().y + correctionBY);
                }
            }
        }
    }
}

bool Board::compareBalls(std::unique_ptr<Fruit>& ballA, std::unique_ptr<Fruit>& ballB)
{
    return ballA->getFruitType() == ballB->getFruitType();
}

int Board::mergeBalls()
{
    int points = 0;
    bool merged = false;
    std::vector<size_t> toRemoveIndices;

    for (size_t i = 0; i < balls.size(); i++) {
        for (size_t j = i + 1; j < balls.size(); j++) {
            auto& ballA = balls[i];
            auto& ballB = balls[j];

            if (compareBalls(ballA, ballB)) {
                // Calculate distance between the centers of the balls
                float deltaY = ballA->getBallPosition().y - ballB->getBallPosition().y;
                float deltaX = ballA->getBallPosition().x - ballB->getBallPosition().x;
                float deltaR = deltaX * deltaX + deltaY * deltaY;
                float distance = std::sqrt(deltaR);

                // Check if balls overlap
                if (distance <= (ballA->getRadius() + ballB->getRadius())) {
                    float averageX = (ballA->getBallPosition().x + ballB->getBallPosition().x) / 2;
                    float averageY = (ballA->getBallPosition().y + ballB->getBallPosition().y) / 2;
                    sf::Vector2f averagePosition(averageX, averageY);
                    std::unique_ptr<Fruit> fruit;

                    switch (ballA->getFruitType())
                    {
                    case FruitType::Blueberry:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Strawberry);
                        points += 2;
                        break;
                    case FruitType::Strawberry:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Appricot);
                        points += 4;
                        break;
                    case FruitType::Appricot:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Apple);
                        points += 8;
                        break;
                    case FruitType::Apple:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Pumpkin);
                        points += 16;
                        break;
                    case FruitType::Pumpkin:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Melon);
                        points += 32;
                        break;
                    case FruitType::Melon:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Coconut);
                        points += 64;
                        break;
                    case FruitType::Coconut:
                        fruit = std::make_unique<Fruit>(averagePosition, FruitType::Pineapple);
                        points += 128;
                        break;
                    case FruitType::Pineapple:
                        // Pineapple to faza końcowa
                        points += 512;
                        break;
                    }

                    if (ballA->getFruitType() != FruitType::Pineapple) {
                        addBall(std::move(fruit));
                    }

                    toRemoveIndices.push_back(i);
                    toRemoveIndices.push_back(j);
                    merged = true;
                    break;
                }
            }
            if (merged) {
                break;
            }
        }
        if (merged) {
            break;
        }
    }

    std::sort(toRemoveIndices.rbegin(), toRemoveIndices.rend());
    for (size_t index : toRemoveIndices) {
        balls.erase(balls.begin() + index);
    }

    return points;
}

int Board::boardFill()
{
    float boardVolume = boardSize.x * boardSize.y;
    float ballsVolume = 0;

    for (auto& ball : balls)
    {
        ballsVolume += 3.1415 * static_cast<float>(ball->getFruitType()) * static_cast<float>(ball->getFruitType());
    }
    
    int fillPercent = (ballsVolume * 100) / (boardVolume * 0.68 * 0.2);
    if (fillPercent > 100)
    {
        fillPercent = 100;
    }
    return fillPercent;
}

void Board::resetBoard()
{
    balls.clear();
}