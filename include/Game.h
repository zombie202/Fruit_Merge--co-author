#pragma once

#include "Game.h"
#include "graphics/UiManager.h"
#include "fruits/Fruit.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <memory>
#include "RankingManager.h"
#include "SFML/Audio/Music.hpp"

class Game {
private:
    UiManager manager;
public:
    void loop();
};

