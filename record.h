#ifndef RECORD_H
#define RECORD_H

#include <string>

struct GameRecord {
    std::string difficulty;
    double timeSpent;
    std::string timestamp;
    GameRecord* next;
};

// Linked list functions
void insertSorted(GameRecord*& head, GameRecord* newRecord);
void printRecords(GameRecord* head);

// File save/load functions
void saveRecords(GameRecord* head);
void loadRecords(GameRecord*& head);

// Utility
std::string getCurrentTimestamp();
int difficultyRank(const std::string& difficulty);

// Memory management
void deleteAllRecords(GameRecord*& head);

#endif
