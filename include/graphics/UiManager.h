#pragma once

#include "SFML/Graphics.hpp"
#include "GameState.h"
#include "graphics/GameWindow.h"
#include "RankingManager.h"
#include "Menu.h"
#include "graphics/ExitWindow.h"
#include "graphics/FinalWindow.h"
#include "SoundManager.h"

class UiManager {
public:
    sf::RenderWindow window;

private:
	GameState currentState;
	GameWindow gameWindow;
    RankingManager rankingManager;
    Menu menu;
    ExitWindow exitWindow;
    FinalWindow finalWindow;
    SoundManager soundManager;
    
public:
    UiManager();
    void gameModeApplyer(float deltaTime);
    void updateState(const GameState& state);
    GameState getCurrentState() const;
    GameWindow& getGameWindow() { return gameWindow; };

private:
	void runMenu();
    void runInstruction();
	void runGame(float deltaTime);
	void runEnd(float deltaTime);
};