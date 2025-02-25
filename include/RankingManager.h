#pragma once

#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


class RankingManager
{
    private:
        std::vector<std::pair<std::string, int>> scoreHistory;
        int actualScore = 0;
    
    public:
        RankingManager();
        ~RankingManager();

        //gettery
        std::vector<std::pair<std::string, int>> getScoreHistory() { return scoreHistory; };
        int getActualScore() { return actualScore; };

        //settery
        void updateActualScore(int points);

        //dodawanie wyniku gracza do rankingu oraz sortowanie wektora
        void addPlayerScore(std::string player);

        //resetowanie aktualnego wyniku
        void resetActualScore() { actualScore = 0; };

        //zapisywanie wyników do pliku
        void saveRanking();

        //wczytywanie wyników z pliku
        void loadRanking();

    friend std::ostream &operator<<(std::ostream &os, std::vector<std::pair<std::string, int>>& scoreHistory);
};

std::ostream &operator<<(std::ostream &os, std::vector<std::pair<std::string, int>>& scoreHistory);