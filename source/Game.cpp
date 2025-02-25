#include "Game.h"

void Game::loop() {
    sf::Clock clock; 

    while (manager.window.isOpen()) {
        // obsługa delta time
        sf::Time deltaTimer = clock.restart();
        float deltaTime = deltaTimer.asSeconds();

        EventHandler::handleEvent(manager.window);

        // Rysowanie tła
        manager.window.clear();
        manager.gameModeApplyer(deltaTime);

        EventHandler::resetVariables();
        // Wyświetlanie okna
        manager.window.display();
    }
}
