#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <utility>

void clearScreen();
void printBoard(const std::vector<std::vector<std::string>>& board, const std::vector<std::vector<bool>>& revealed, int rows, int cols);
void saveGame(const std::vector<std::vector<std::string>>& board,
              const std::vector<std::vector<bool>>& revealed,
              const std::vector<std::string>& deck,
              const std::vector<std::string>& fruitPool,
              int rows, int cols, int pairsFound, int totalPairs, double elapsedTime,
              bool isFirstCardFlipped, std::pair<int, int> firstFlippedCard = std::make_pair(-1, -1));
bool loadGame(std::vector<std::vector<std::string>>& board,
              std::vector<std::vector<bool>>& revealed,
              std::vector<std::string>& deck,
              std::vector<std::string>& fruitPool,
              int& rows, int& cols, int& pairsFound, int& totalPairs, double& elapsedTime,
              bool& isFirstCardFlipped, std::pair<int, int>& firstFlippedCard);
bool hasSavedGame();
std::pair<int, int> getSelection(const std::vector<std::vector<bool>>& revealed, int rows, int cols);
bool getDifficultyLevel(int& rows, int& cols);
void fisherYatesShuffle(std::vector<std::string>& vec);

#endif