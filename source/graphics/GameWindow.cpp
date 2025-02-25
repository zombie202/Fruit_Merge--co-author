#include "graphics/GameWindow.h"
#include <filesystem>

GameWindow::GameWindow()
{
    loadBackgroundTexture();
    if (!loadFont()) {
        std::cerr << "Failed to load font. Ranking text will not be displayed correctly." << std::endl;
    }
    board = std::make_unique<Board>(sf::Vector2f(boardSizeX, boardSizeY));

    progressbar.setPosition(sf::Vector2f(1000-350, boardSizeY));
    initializeScoreText();
}

GameState GameWindow::draw(sf::RenderWindow& window, RankingManager& rankingManager, float deltaTime, SoundManager& soundManager)
{
    window.draw(backgroundSprite);
    int points = drawFruits(window, deltaTime);

    if (points != 0)
    {
        rankingManager.updateActualScore(points);
        soundManager.playMergeSound();
    }
    
    updateScoreText(rankingManager.getActualScore());
    window.draw(scoreText);

    updateRankingTexts(rankingManager.getScoreHistory());

    
    // Rysowanie tekstów rankingu
    for (const auto& text : rankingTexts)
    {
        window.draw(text);
    }

    drawCloud(window);
    progressbar.draw(window);

    if (checkEndOfGame())
    {
        isFinished = true;
        return GameState::End;
    }

    if (EventHandler::leftMouseButtonClicked && !(isFinished))
    {
        renderFruit(window, soundManager);
    }

    // renderFruit(window); //na potrzeby testów
    return GameState::Game;
}

const sf::Sprite& GameWindow::getBackgroundSprite() const
{
    return backgroundSprite;
}

void GameWindow::loadBackgroundTexture()
{
    if (!backgroundTexture.loadFromFile("assets/boardBackground.png")) {
        std::cerr << "Error loading background texture from assets/boardBackground.png" << std::endl;
    }
    else {
        backgroundSprite.setTexture(backgroundTexture);
    }
}

void GameWindow::updateRankingTexts(const std::vector<std::pair<std::string, int>>& ranking)
{
    rankingTexts.clear();
    
    sf::Text title;
    title.setFont(font);
    title.setString("Ranking");
    title.setCharacterSize(24);
    title.setFillColor(sf::Color::White);
    title.setPosition(650, 120); // Ustaw pozycję tytułu (dostosuj według potrzeby)
    rankingTexts.push_back(title);
    
    int yPosition = 160; // Początkowa pozycja Y dla elementów rankingu
    
    for (size_t i = 0; i < ranking.size(); ++i)
    {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setString(std::to_string(i + 1) + ". " + ranking[i].first + " ..... " + std::to_string(ranking[i].second));
        text.setPosition(650, yPosition); // Ustaw pozycję X i Y dla każdego elementu
        rankingTexts.push_back(text);
        yPosition += 30; // Odstęp między liniami
    }
}

void GameWindow::updateScoreText(int score) {
    scoreText.setString("Score: " + std::to_string(score));
}

void GameWindow::initializeScoreText() {
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(650, 50);
    updateScoreText(0);
}

bool GameWindow::loadFont()
{
    // TODO: Ustawić ścieżkę do pliku czcionki, teraz jej nie czyta prawidłowo
    std::string fontPath = "assets/kalamLight.ttf";

    // Sprawdzenie, czy plik istnieje
    if (!std::filesystem::exists(fontPath)) {
        std::cerr << "Font file does not exist: " << fontPath << std::endl;
        return false;
    } else {
        std::cout << "Font file exists: " << fontPath << std::endl;
    }

    if (!font.loadFromFile(fontPath)) {
        std::cerr << "Error loading font from " << fontPath << std::endl;
        return false;
    }
    return true;
}

int GameWindow::drawFruits(sf::RenderWindow& window, float deltaTime)
{
    for (const auto &fruit : board->getBalls())
    {
        fruit->synchronizePosition();
        window.draw(*fruit);
    }

    board->updatePosition(deltaTime);
    int points = board->mergeBalls();
    board->bounce();
    board->otherBallsBounce();
    return points;
}

void GameWindow::renderFruit(sf::RenderWindow& window, SoundManager& soundManager)
{
    std::vector<double> probabilities = {0.6, 0.3, 0.1}; // Prawdopodobieństwa dla 1, 2 i 3 odpowiednio

    std::random_device rd;
    std::mt19937 generator(rd());

    std::discrete_distribution<int> distribution(probabilities.begin(), probabilities.end());
    
    FruitType generatedFruitType;

    switch (distribution(generator))
    {
        case 0:
            generatedFruitType = FruitType::Blueberry;
            break;
        case 1:
            generatedFruitType = FruitType::Strawberry;
            break;
        case 2:
            generatedFruitType = FruitType::Appricot;
            break;
    }

    float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
    std::unique_ptr<Fruit> fruit = std::make_unique<Fruit>(sf::Vector2f(mouseX, droppingHeight), generatedFruitType);
    fruit->setVelocity(sf::Vector2f(0.f, 3.f));
    board->addBall(std::move(fruit));
    soundManager.playPopSound();
}

void GameWindow::drawCloud(sf::RenderWindow& window)
{
    float mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
    if (mouseX < cloud.getWidth()/2)
    {
        mouseX = cloud.getWidth()/2;
    }
    if (mouseX > boardSizeX - cloud.getWidth()/2)
    {
        mouseX = boardSizeX - cloud.getWidth()/2;
    }
    cloud.setCloudPosition(sf::Vector2f(mouseX, droppingHeight));
    window.draw(cloud);
}

void GameWindow::resetGame(RankingManager& rankingManager)
{
    board->resetBoard();
    rankingManager.resetActualScore();
    isFinished = false;
}

bool GameWindow::checkEndOfGame()
{
    int percentage = board->boardFill();
    progressbar.setFill(percentage);
    if (percentage == 100)
    {
        return true;
    }
    return false;
}