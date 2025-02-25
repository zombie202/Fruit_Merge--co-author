#include "RankingManager.h"

RankingManager::RankingManager()
{
    try
    {
    loadRanking();
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Plik scoreHistory.txt jeszcze nie istnieje, powstanie przy zakończeniu pracy programu." << std::endl;
    }
}

RankingManager::~RankingManager()
{
    saveRanking();
}

void RankingManager::updateActualScore(int points)
{
    actualScore += points;
}

void RankingManager::addPlayerScore(std::string player)
{
    std::pair<std::string, int> newScore;
    newScore.first = player;
    newScore.second = actualScore;
    scoreHistory.push_back(newScore);
    std::sort(scoreHistory.begin(), scoreHistory.end(),
        [&](std::pair<std::string, int> a, std::pair<std::string, int> b)
        { return a.second > b.second; });
    while (scoreHistory.size() > 10)
    {
        scoreHistory.pop_back();
    }
}

void RankingManager::loadRanking()
{
    scoreHistory.clear();

    std::fstream file;
    file.open("assets/scoreHistory.txt", std::ios::in);
    if (!file.is_open())
    {
        throw std::runtime_error("Nie można otworzyć pliku scoreHistory.txt");
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string player;
        std::string scoreString;
        while(std::getline(iss, player, ':'))
        {
            std::getline(iss, scoreString);
            scoreHistory.push_back(std::pair<std::string, int>(player, std::stoi(scoreString))); 
        }
    }
    file.close();
}

void RankingManager::saveRanking()
{
    std::ofstream file;
    file.open("assets/scoreHistory.txt", std::ios::out | std::ios::trunc);
    if (!file.is_open())
    {
        throw std::runtime_error("Nie można otworzyć pliku scoreHistory.txt");
    }

    file << scoreHistory;
    file.close();
}

std::ostream &operator<<(std::ostream &os, std::vector<std::pair<std::string, int>>& scoreHistory)
{
    for (auto& pair : scoreHistory)
    {
        os << pair.first << ':' << pair.second << std::endl;
    }

    return os;
}