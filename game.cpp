#include "game.h"
#include "utils.h"
#include "fruitpool.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

GameRecord* recordHead = nullptr;

// 1. Initializing Gameplay
// Start of the game, initalized through the main function

void runProgram(bool loadSaved) {
    int rows, cols, timelimit;
    vector<vector<string>> board;
    vector<vector<bool>> revealed;
    vector<string> deck;
    int pairsFound = 0, totalPairs = 0;
    double elapsedTime = 0.0;
    chrono::steady_clock::time_point startTime;
    bool isFirstCardFlipped = false;
    pair<int, int> firstFlippedCard = make_pair(-1, -1);

    // Load saved game if applicable

    if (loadSaved && loadGame(board, revealed, deck, fruitNames, rows, cols, timelimit,
                              pairsFound, totalPairs, elapsedTime, isFirstCardFlipped, firstFlippedCard)) {
        chrono::steady_clock::time_point now = chrono::steady_clock::now();
        chrono::steady_clock::duration elapsedDuration = chrono::duration_cast<chrono::steady_clock::duration>(chrono::duration<double>(elapsedTime));
        startTime = now - elapsedDuration;

    // New game generation based on user input

    } else {
        getDifficultyLevel(rows, cols, timelimit);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Custom function for generating a new game: grid size and fruit pairs

        if ((rows * cols) % 2 != 0) {
            cerr << "Error: Grid size (rows * cols) must be even." << endl;
            return;
        }

        const int pairsNeeded = rows * cols / 2;
        if (fruitNames.size() < static_cast<size_t>(pairsNeeded)) {
            cerr << "Error: Not enough fruits in the pool for selected grid size." << endl;
            return;
        }

        // Shuffle the fruit names and select the required number of pairs 
        // Generated with the Fisher-Yates shuffle algorithm

        vector<string> shuffledFruits = fruitNames;
        fisherYatesShuffle(shuffledFruits);
        vector<string> selectedFruits(shuffledFruits.begin(), shuffledFruits.begin() + pairsNeeded);

        deck.clear();
        for (const auto& fruit : selectedFruits) {
            deck.push_back(fruit);
            deck.push_back(fruit);
        }
        fisherYatesShuffle(deck);

        // Initialize the board and revealed state

        board.assign(rows, vector<string>(cols));
        revealed.assign(rows, vector<bool>(cols, false));
        int idx = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                board[r][c] = deck[idx++];
            }
        }
        // Time limit and pairs found initialization

        totalPairs = rows * cols / 2;
        startTime = chrono::steady_clock::now();
    }

    // Game loop: continue until all pairs are found or time runs out

    while (pairsFound < totalPairs) {
        clearScreen();
        cout << "Memory Game: find all " << totalPairs << " pairs!" << endl << endl;
        printBoard(board, revealed, rows, cols);

        if (isFirstCardFlipped) {
            cout << "\nSelect second card:" << endl;
            pair<int, int> second = getSelection(revealed, rows, cols);
            if (second.first == -1) return;
            if (second.first == -2) {
                auto endTime = chrono::steady_clock::now();
                chrono::duration<double> elapsed = endTime - startTime;
                saveGame(board, revealed, deck, fruitNames, rows, cols, timelimit, pairsFound, totalPairs, elapsed.count(), true, firstFlippedCard);
                return;
            }
            int r2 = second.first, c2 = second.second;
            revealed[r2][c2] = true;
            clearScreen();
            printBoard(board, revealed, rows, cols);

            int r1 = firstFlippedCard.first, c1 = firstFlippedCard.second;
            if (board[r1][c1] == board[r2][c2]) {
                cout << "\nMatched! " << board[r1][c1] << endl;
                pairsFound++;
            } else {
                cout << "\nNot a match." << endl;
                this_thread::sleep_for(chrono::milliseconds(1500));
                revealed[r1][c1] = revealed[r2][c2] = false;
            }
            isFirstCardFlipped = false;

            // Show the board after each turn

            cout << "\n(Found " << pairsFound << " of " << totalPairs << " pairs.)" << endl;
            cout << "Press Enter to continue...";

            // Wait for user input before continuing

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        } else {
            cout << "\nSelect first card:" << endl;
            pair<int, int> first = getSelection(revealed, rows, cols);
            if (first.first == -1) return;
            if (first.first == -2) {
                auto endTime = chrono::steady_clock::now();
                chrono::duration<double> elapsed = endTime - startTime;
                saveGame(board, revealed, deck, fruitNames, rows, cols, timelimit, pairsFound, totalPairs, elapsed.count(), false);
                return;
            }
            int r1 = first.first, c1 = first.second;
            revealed[r1][c1] = true;
            firstFlippedCard = make_pair(r1, c1);
            isFirstCardFlipped = true;

            // Just show the board after first card
            
            clearScreen();
            cout << "Memory Game: find all " << totalPairs << " pairs!" << endl << endl;
            printBoard(board, revealed, rows, cols);

            continue;  
            
            // Skip the status display and continue to second card selection
        }

        // Check for time limit
        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsed = endTime - startTime;
        if (elapsed.count() >= timelimit) {
            clearScreen();
            cout << "Sorry, no time left." << endl;
            return;
        }
    }

    // Game over: all pairs found

    clearScreen();
    auto endTime = chrono::steady_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    cout << "Congratulations! You found all " << totalPairs << " pairs!" << endl;
    cout << "Time taken: " << fixed << std::setprecision(2) << elapsed.count() << " seconds." << endl;
    
    // Save the game record

    string difficulty = (rows == 4 && cols == 2) ? "Easy" :
                       (rows == 4 && cols == 4) ? "Medium" :
                       (rows == 6 && cols == 4) ? "Hard" : "Custom";
    double timeSpent = elapsed.count();
    string timeNow = getCurrentTimestamp();

    GameRecord* newRec = new GameRecord{difficulty, timeSpent, timeNow, nullptr};
    insertSorted(recordHead, newRec);
    saveRecords(recordHead);

    // Sorted High Scores

    cout << "\nHigh Scores:\n";
    printRecords(recordHead);
    
    // Option to delete all records

    cout << "\nWould you like to delete all records? (Y/N): ";
    char deleteChoice;
    cin >> deleteChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (toupper(deleteChoice) == 'Y') {
        deleteAllRecords(recordHead);
        cout << "All records have been deleted.\n";
        cout << "Press Enter to continue...";
        cin.get();
    }

    remove("game_save.txt");
}

// 2. Replay Game Option
// Function to provide the user to play another round

bool shouldRestart() {
    char decision;
    cout << "Do you want to play again? (y/n): ";
    cin >> decision;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    decision = toupper(decision);
    if (decision == 'Y') {
        return true;
    } else if (decision == 'N') {
        cout << "Thanks for playing! Goodbye!" << endl;
        return false;
    } else {
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
        return shouldRestart();
    }
}
