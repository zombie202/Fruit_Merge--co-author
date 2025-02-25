#include "graphics/UiManager.h"

const int winSide = 1000;
const sf::Vector2u winSize(winSide, winSide);
sf::Sprite Menu::instBackground;								
sf::Sprite Menu::background;

UiManager::UiManager() : currentState(GameState::Menu)
{
    menu.width = winSide;
    menu.height = winSide;
    //  Flaga (sf::Style::Titlebar | sf::Style::Close) odpowiada za brak możliwości rozszerzenia okna
    //  i w oknie wyświetla się cała gra i jedynie pasek z tytułem danego okna, a wtym przypadku "Fruit Merge"
	window.create(sf::VideoMode(winSide, winSide), "Fruit Merge", sf::Style::Titlebar | sf::Style::Close);
	window.setSize(winSize);
	window.setFramerateLimit(60);
    soundManager.playMusic();
}

void UiManager::gameModeApplyer(float deltaTime)
{
    // --------------------------------------------------------------------------------------//
    // State machine that switches beetwen states of the game acordingly to current state
    // --------------------------------------------------------------------------------------//
	switch (currentState)
	{
		case GameState::Menu:
			runMenu();
			break;
		case GameState::Instruction:
			runInstruction();
			break;
		case GameState::Game:
			runGame(deltaTime);
			break;
		case GameState::End:
			runEnd(deltaTime);
			break;
	}
    // --------------------------------------------------------------------------------------//
    // Display exit window, must be in there so it displays above everything else
    if (EventHandler::escapeClicked)
    {
        exitWindow.update(window);
        exitWindow.draw(window);
        if (exitWindow.yesClicked(EventHandler::leftMouseButtonClicked))
        {
            window.close();
            EventHandler::escapeClicked = false;
        }
        if (exitWindow.noClicked(EventHandler::leftMouseButtonClicked))
        {
            EventHandler::escapeClicked = false;
        }
    }
}

void UiManager::updateState(const GameState& state)
{
	currentState = state;
}

GameState UiManager::getCurrentState() const {
    return currentState;
}

void UiManager::runMenu()
{
    // --------------------------------------------------------------------------------------//
    // Display Menu and chandle wchich state to go next
    // --------------------------------------------------------------------------------------//
    if (currentState == GameState::Menu)
    {
        //  Wykorzystujemy metod� klasy Menu do narysowania t�a i innych element�w menu
        menu.drawMainMenu(window);
        float mousePosX = static_cast<float>(sf::Mouse::getPosition(window).x);
        float mousePosY = static_cast<float>(sf::Mouse::getPosition(window).y);
        if (Menu::getBackground().getGlobalBounds().contains(mousePosX, mousePosY))
        {
            for (size_t i = 0; i < menu.menuItems.size() - 2; ++i)
            {
                //  Sprawdzamy, czy myszka znajduje si� nad danym przyciskiem
                //  Je�li tak, to kolor napisu zmieni si� na magenta 
                if (menu.IsMouseOver(window, i))
                {
                    menu.menuItems[i].setFillColor(sf::Color::Magenta);
                }
                else
                {
                    menu.menuItems[i].setFillColor(sf::Color::White);
                }
            }
        }
        if (EventHandler::leftMouseButtonClicked)
        {
            for (size_t i = 0; i < menu.menuItems.size() - 2; ++i)
            {
                if (menu.IsMouseOver(window, i))
                {
                    // Handle menu item selection
                    switch (i)
                    {
                    case 0:
                        // Start Game selected
                        gameWindow.resetGame(rankingManager);
                        updateState(GameState::Game);
                        break;
                    case 1:
                        // Description selected
                        updateState(GameState::Instruction);
                        break;
                    case 2:
                        // Quit selected
                        window.close();
                        break;
                    }
                }
            }
        }
    }
}

void UiManager::runInstruction()
{
    // --------------------------------------------------------------------------------------//
    // Display instruction window
    // --------------------------------------------------------------------------------------//
    if (currentState == GameState::Instruction)
    {
        menu.drawInstruction(window);
        float mousePosX = static_cast<float>(sf::Mouse::getPosition(window).x);
        float mousePosY = static_cast<float>(sf::Mouse::getPosition(window).y);
        if (Menu::getInstBackground().getGlobalBounds().contains(mousePosX, mousePosY))
        {
            if (menu.IsMouseOver(window, 4))
            {
                menu.menuItems[4].setFillColor(sf::Color::Magenta);
            }
            else
            {
                menu.menuItems[4].setFillColor(sf::Color::White);
            }
        }
        if (EventHandler::leftMouseButtonClicked)
        {
            if (menu.IsMouseOver(window, 4))
            {
                updateState(GameState::Menu);
            }
        }
    }
}

void UiManager::runGame(float deltaTime)
{
    // --------------------------------------------------------------------------------------//
    // Run game
    // --------------------------------------------------------------------------------------//
	if(gameWindow.draw(window, rankingManager, deltaTime, soundManager) == GameState::End)
	{
		updateState(GameState::End);
	}
}

void UiManager::runEnd(float deltaTime)
{
    // --------------------------------------------------------------------------------------//
    // Draw window in which user can input name by which he wants his score saved
    // which then gets saved and displayed
    // --------------------------------------------------------------------------------------//
	gameWindow.draw(window, rankingManager, deltaTime, soundManager);
    finalWindow.update(window);
    finalWindow.draw(window);
    if (finalWindow.enterClicked(EventHandler::leftMouseButtonClicked) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (finalWindow.getUsername().size() > 0)
        {
            rankingManager.addPlayerScore(finalWindow.getUsername());
            updateState(GameState::Menu);
        }
    }
}
