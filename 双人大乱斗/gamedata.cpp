#include"gamedata.h"

#include <cstring>

void GameData::saveToFile(const std::string& filename)
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        file.write(reinterpret_cast<const char*>(&player1Wins), sizeof(player1Wins));
        file.write(reinterpret_cast<const char*>(&player2Wins), sizeof(player2Wins));
        file.write(reinterpret_cast<const char*>(&lastWinner), sizeof(lastWinner));
        file.write(reinterpret_cast<const char*>(&totalGames), sizeof(totalGames));
        file.close();
    }
}

bool GameData::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open())
    {
        file.read(reinterpret_cast<char*>(&player1Wins), sizeof(player1Wins));
        file.read(reinterpret_cast<char*>(&player2Wins), sizeof(player2Wins));
        file.read(reinterpret_cast<char*>(&lastWinner), sizeof(lastWinner));
        file.read(reinterpret_cast<char*>(&totalGames), sizeof(totalGames));
        file.close();
        return true;
    }
    return false;
}

void GameData::reset()
{
    player1Wins = 0;
    player2Wins = 0;
    lastWinner = 0;
    totalGames = 0;
}