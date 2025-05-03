#include "game.h"
#include "utils.h"
#include "fruitpool.h"
#include "record.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;


// Head pointer for the linked list of game records
GameRecord* recordHead = nullptr; 




// Run the game program, allowing the player to find matching fruit pairs on a grid, with options to load a saved game, save progress, and manage high scores.
// Input is from the - loadSaved (bool), which indicates whether to attempt loading a previously saved game state.
// The function manages the game loop, updates the console display, and modifies global game records.

void runProgram(bool loadSaved) {
    int rows, cols;
    vector<vector<string>> board;
    vector<vector<bool>> revealed;
    vector<string> deck;
    int pairsFound = 0, totalPairs = 0;
    double elapsedTime = 0.0;
    chrono::steady_clock::time_point startTime;
    bool isFirstCardFlipped = false;
    pair<int, int> firstFlippedCard = make_pair(-1, -1);

    // Check if resuming a saved game
    if (loadSaved && loadGame(board, revealed, deck, fruitNames, rows, cols, 
                              pairsFound, totalPairs, elapsedTime, isFirstCardFlipped, firstFlippedCard)) {
        // Resume timer by adjusting start time with elapsed time from saved game
        chrono::steady_clock::time_point now = chrono::steady_clock::now();
        chrono::steady_clock::duration elapsedDuration = chrono::duration_cast<chrono::steady_clock::duration>(chrono::duration<double>(elapsedTime));
        startTime = now - elapsedDuration;
    } else {
        // Start new game: Select difficulty and set up game board
        getDifficultyLevel(rows, cols);

        if ((rows * cols) % 2 != 0) {
            cerr << "Error: Grid size (rows * cols) must be even." << endl;
            return;
        }

        // Determine number of pairs needed
        const int pairsNeeded = rows * cols / 2;
        if (fruitNames.size() < static_cast<size_t>(pairsNeeded)) {
            cerr << "Error: Not enough fruits in the pool for selected grid size." << endl;
            return;
        }

        // Shuffle fruits and select the necessary amount
        vector<string> shuffledFruits = fruitNames;
        fisherYatesShuffle(shuffledFruits);
        vector<string> selectedFruits(shuffledFruits.begin(), shuffledFruits.begin() + pairsNeeded);

        // Build deck with pairs and shuffle deck
        deck.clear();
        for (const auto& fruit : selectedFruits) {
            deck.push_back(fruit);
            deck.push_back(fruit);
        }
        fisherYatesShuffle(deck);

        // Set up the game board and the revealed matrix
        board.assign(rows, vector<string>(cols));
        revealed.assign(rows, vector<bool>(cols, false));
        int idx = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                board[r][c] = deck[idx++];
            }
        }
        totalPairs = rows * cols / 2;
        startTime = chrono::steady_clock::now();
    }

    // Main game loop until all pairs are found
    while (pairsFound < totalPairs) {
        clearScreen();
        cout << "Memory Game: find all " << totalPairs << " pairs!" << endl << endl;
        printBoard(board, revealed, rows, cols);

        if (isFirstCardFlipped) {
            // Second card selection
            cout << "\nSelect second card:" << endl;
            pair<int, int> second = getSelection(revealed, rows, cols);
            if (second.first == -1) return;  // Quit game
            if (second.first == -2) {
                // Save game then quit
                auto endTime = chrono::steady_clock::now();
                chrono::duration<double> elapsed = endTime - startTime;
                saveGame(board, revealed, deck, fruitNames, rows, cols, pairsFound, totalPairs, elapsed.count(), true, firstFlippedCard);
                return;
            }
            int r2 = second.first, c2 = second.second;
            revealed[r2][c2] = true;
            clearScreen();
            printBoard(board, revealed, rows, cols);

            int r1 = firstFlippedCard.first, c1 = firstFlippedCard.second;
            // Check for a match between the two cards
            if (board[r1][c1] == board[r2][c2]) {
                cout << "\nMatched! " << board[r1][c1] << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
                pairsFound++;
            } else {
                cout << "\nNot a match." << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
                revealed[r1][c1] = revealed[r2][c2] = false;
            }
            isFirstCardFlipped = false;
            cout << "\n(Found " << pairsFound << " of " << totalPairs << " pairs.)" << endl;
            cout << "Press Enter to continue...";
            string dummy;
            getline(cin, dummy);
        } else {
            // First card selection
            cout << "\nSelect first card:" << endl;
            pair<int, int> first = getSelection(revealed, rows, cols);
            if (first.first == -1) return;  // Quit game
            if (first.first == -2) {
                // Save game then quit
                auto endTime = chrono::steady_clock::now();
                chrono::duration<double> elapsed = endTime - startTime;
                saveGame(board, revealed, deck, fruitNames, rows, cols, pairsFound, totalPairs, elapsed.count(), false, firstFlippedCard);
                return;
            }
            int r1 = first.first, c1 = first.second;
            revealed[r1][c1] = true;
            firstFlippedCard = make_pair(r1, c1);
            isFirstCardFlipped = true;
            clearScreen();
            cout << "Memory Game: find all " << totalPairs << " pairs!" << endl << endl;
            printBoard(board, revealed, rows, cols);
        }
    }

    // End game: all pairs have been found
    clearScreen();
    auto endTime = chrono::steady_clock::now();
    chrono::duration<double> elapsed = endTime - startTime;
    cout << "Congratulations! You found all " << totalPairs << " pairs!" << endl;
    cout << "Time taken: " << fixed << setprecision(2) << elapsed.count() << " seconds." << endl;
    
    // Determine difficulty based on grid dimensions
    string difficulty = (rows == 4 && cols == 2) ? "Easy" :
                        (rows == 4 && cols == 4) ? "Medium" :
                        (rows == 6 && cols == 4) ? "Hard" : "Custom";
    double timeSpent = elapsed.count();
    string timeNow = getCurrentTimestamp();

    // Create a new game record and update the high scores
    GameRecord* newRec = new GameRecord{difficulty, timeSpent, timeNow, nullptr};
    insertSorted(recordHead, newRec);
    saveRecords(recordHead);

    cout << "\nHigh Scores:\n";
    printRecords(recordHead);
    
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

    // Remove saved game file after finishing the game
    remove("game_save.txt");
}




// This function prompts the user to decide whether to play the game again and validates their input.
// The function reads user input directly from the console (y/n).
// Returns true if the user chooses to play again ('y' or 'Y'), false if they choose to quit ('n' or 'N'). Recursively calls itself for invalid inputs.

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
