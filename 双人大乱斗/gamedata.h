#pragma once

#include <string>
#include <fstream>

struct GameData
{
    int player1Wins = 0;
    int player2Wins = 0;
    int lastWinner = 0; // 0: Œﬁ, 1: P1ªÒ §, 2: P2ªÒ §
    int totalGames = 0;

    void saveToFile(const std::string& filename = "game_save.dat");
    bool loadFromFile(const std::string& filename = "game_save.dat");
    void reset();
};
