#pragma once
#include "core/Board.h"
#include "fruits/Fruit.h"
#include "core/Board.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include <memory>
#include "EventHandler.h"
#include "RankingManager.h"
#include "GameState.h"
#include "graphics/Cloud.h"
#include "SoundManager.h"
#include <random>
#include "graphics/Progressbar.h"

constexpr float boardSizeX = 592.0f;
constexpr float boardSizeY = 834.f;
constexpr float droppingHeight = 100.f;

class GameWindow
{
private:
	std::unique_ptr<Board> board;
	Cloud cloud;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Text scoreText;
	void loadBackgroundTexture();
    sf::Font font;
    bool loadFont();
	Progressbar progressbar;
    std::vector<sf::Text> rankingTexts; // Lista tekstów dla rankingu
	bool isFinished = false;
	
public:
	GameWindow();
	GameState draw(sf::RenderWindow& window, RankingManager& rankingManager, float deltaTime, SoundManager& soundManager);
	const sf::Sprite& getBackgroundSprite() const; // Metoda dost�pu do sprite'a t�a
    void updateRankingTexts(const std::vector<std::pair<std::string, int>>& ranking); // Aktualizacja tekstów rankingu
	int drawFruits(sf::RenderWindow& window, float deltaTime);
	void mergeFruits();
    void renderFruit(sf::RenderWindow& window, SoundManager& soundManager);
	void updateScoreText(int score);
	void initializeScoreText();
	void drawCloud(sf::RenderWindow& window);
	void resetGame(RankingManager& rankingManager);
	bool checkEndOfGame();
};