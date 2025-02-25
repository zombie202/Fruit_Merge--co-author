#ifndef BOARD_H
#define BOARD_H

#include "SFML/Graphics.hpp"
#include "Ball.h"
#include "fruits/Fruit.h"

#include <vector>
#include <memory>

class Board
{
private:
    sf::Vector2f boardSize;
    const float viscosity = 0.3;
    const float friction = 0.8;
    const float airResistance = 0.9;
    sf::Vector2f gravity = sf::Vector2f(0, 0.15);
    std::vector<std::unique_ptr<Fruit>> balls;

public:
    Board(sf::Vector2f _board_size);  // Usunięto drugi konstruktor
    void addBall(std::unique_ptr<Fruit> ball);
    void removeBall(std::unique_ptr<Fruit> ball);

    // Gettery
    const std::vector<std::unique_ptr<Fruit>>& getBalls() const { return balls; };
    sf::Vector2f getBoardSize() { return boardSize; };

    // Dostosowuje pozycję wszystkich obiektów na podstawie ich prędkości
    void updatePosition(float deltaTime);

    // Odpowiada za odbijanie się obiektów od ścian
    void bounce();

    // Odpowiada za odbijanie się obiektów od siebie
    void otherBallsBounce();
    
    // Odpowiada za sprawdzenie czy obiekty są tej samej wielkości
    bool compareBalls(std::unique_ptr<Fruit>& ballA, std::unique_ptr<Fruit>& ballB);

    // Odpowiada za połączenie kulek
    int mergeBalls();

    // Sprawdza czy gra powinna zostać zakończona
    int boardFill();

    // Odpowiada za opróżnienie boardu z kulek
    void resetBoard();
};

#endif // BOARD_H
