#include "utils.h"
#include "fruitpool.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <unistd.h>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 1. Game Board Generation
 // Find the longest word in fruitpool for block width and account for color codes
void printBoard(const vector<vector<string>>& board, const vector<vector<bool>>& revealed, int rows, int cols) {
    size_t maxLength = 0;
    for (const auto& fruit : fruitNames) {
        maxLength = max(maxLength, fruit.length());
    }
    
    // Set block width (add 2 padding on each side for centering)
    const int blockWidth = maxLength + 4;  
    
    // Print column numbers
    cout << "    ";
    for (int c = 0; c < cols; c++) {
        string colNum = to_string(c);
        int padding = (blockWidth - colNum.length()) / 2;
        cout << string(padding, ' ') << colNum << string(blockWidth - padding - colNum.length(), ' ');
    }
    cout << "\n   +" << string(cols * blockWidth, '-') << "+\n";

    // Print board
    // Use actual content length for padding calculation
    for (int r = 0; r < rows; r++) {
        cout << setw(2) << r << " |";
        for (int c = 0; c < cols; c++) {
            string displayContent;
            string content;
            if (revealed[r][c]) {
                displayContent = fruitColors[board[r][c]] + board[r][c] + "\033[0m";
                content = board[r][c];  
            } else {
                displayContent = "*";
                content = "*";
            }
            
            // Calculate padding based on actual content length, not including color codes
            int padding = (blockWidth - content.length()) / 2;
            cout << string(padding, ' ') << displayContent << string(blockWidth - padding - content.length(), ' ');
        }
        cout << " |\n";
    }
    cout << "   +" << string(cols * blockWidth, '-') << "+\n";
}

// 2. Save Game Function

void saveGame(const vector<vector<string>>& board,
              const vector<vector<bool>>& revealed,
              const vector<string>& deck,
              const vector<string>& fruitPool,
              int rows, int cols, int timelimit,
              int pairsFound, int totalPairs,
              double elapsedTime,
              bool isFirstCardFlipped,
              pair<int, int> firstFlippedCard) {
    ofstream outFile("game_save.txt");
    if (!outFile) {
        cout << "Error: Could not save game." << endl;
        return;
    }

    outFile << rows << " " << cols << " " << timelimit << "\n";
    outFile << pairsFound << " " << totalPairs << " " << elapsedTime << "\n";

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int idx = find(fruitPool.begin(), fruitPool.end(), board[r][c]) - fruitPool.begin();
            outFile << idx << " ";
        }
        outFile << "\n";
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            outFile << (revealed[r][c] ? 1 : 0) << " ";
        }
        outFile << "\n";
    }

    outFile << deck.size() << "\n";
    for (auto& card : deck) {
        int idx = find(fruitPool.begin(), fruitPool.end(), card) - fruitPool.begin();
        outFile << idx << " ";
    }
    outFile << "\n";

    outFile << fruitPool.size() << "\n";
    for (size_t i = 0; i < fruitPool.size(); i++) {
        outFile << i << " " << fruitPool[i] << "\n";
    }

    outFile << (isFirstCardFlipped ? 1 : 0) << " ";
    if (isFirstCardFlipped) {
        outFile << firstFlippedCard.first << " " << firstFlippedCard.second << "\n";
    } else {
        outFile << "\n";
    }

    outFile.close();
    cout << "Game saved successfully.\n";
}

// 3. Load Game Function

bool loadGame(vector<vector<string>>& board,
              vector<vector<bool>>& revealed,
              vector<string>& deck,
              vector<string>& fruitPool,
              int& rows, int& cols, int& timelimit,
              int& pairsFound, int& totalPairs,
              double& elapsedTime,
              bool& isFirstCardFlipped,
              pair<int, int>& firstFlippedCard) {
    ifstream inFile("game_save.txt");
    if (!inFile) {
        cout << "No saved game found.\n";
        return false;
    }

    if (!(inFile >> rows >> cols >> timelimit)) return false;
    if (!(inFile >> pairsFound >> totalPairs >> elapsedTime)) return false;

    board.resize(rows, vector<string>(cols));
    revealed.resize(rows, vector<bool>(cols));

    vector<int> boardIndices(rows * cols);
    for (int& idx : boardIndices)
        inFile >> idx;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int temp;
            if (!(inFile >> temp)) {
                return false;  // Error handling
            }
            revealed[r][c] = (temp == 1);
        }
    }

    int deckSize;
    inFile >> deckSize;
    deck.resize(deckSize);
    vector<int> deckIndices(deckSize);
    for (int& idx : deckIndices)
        inFile >> idx;

    int fruitPoolSize;
    inFile >> fruitPoolSize;
    fruitPool.resize(fruitPoolSize);
    for (int i = 0; i < fruitPoolSize; i++) {
        int idx;
        inFile >> idx;
        inFile.ignore();
        getline(inFile, fruitPool[idx]);
    }

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            board[r][c] = fruitPool[boardIndices[r * cols + c]];

    for (int i = 0; i < deckSize; i++)
        deck[i] = fruitPool[deckIndices[i]];

    int flipped;
    inFile >> flipped;
    isFirstCardFlipped = (flipped == 1);
    if (isFirstCardFlipped)
        inFile >> firstFlippedCard.first >> firstFlippedCard.second;

    inFile.close();
    return true;
}

// 4. Initalizing Saved game

bool hasSavedGame() {
    vector<vector<string>> board;
    vector<vector<bool>> revealed;
    vector<string> deck;
    vector<string> fruitPool;
    int rows, cols, timelimit;
    int pairsFound, totalPairs;
    double elapsedTime;
    bool isFirstCardFlipped;
    pair<int, int> firstFlippedCard;

    return loadGame(board, revealed, deck, fruitPool, rows, cols, timelimit,
                    pairsFound, totalPairs, elapsedTime, isFirstCardFlipped, firstFlippedCard);
}

// 5. Save game or Quit Game Option

pair<int, int> getSelection(const vector<vector<bool>>& revealed, int rows, int cols) {
    string input;
    int r, c;
    while (true) {
        cout << "Enter row and col (e.g. \"1 2\"), 'q' to quit, or 's' to save and quit: ";
        getline(cin, input);

        if (input == "q" || input == "Q")
            return make_pair(-1, -1);
        if (input == "s" || input == "S")
            return make_pair(-2, -2);

        istringstream iss(input);
        if (!(iss >> r >> c)) {
            cout << "Invalid input. Enter two numbers, 'q', or 's'.\n";
            continue;
        }
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            if (!revealed[r][c]) {
                return make_pair(r, c);
            } else {
                cout << "That card is already revealed. Pick another.\n";
            }
        } else {
            cout << "Out of range. 0 <= row < " << rows
                 << ", 0 <= col < " << cols << ".\n";
        }
    }
}

// 6. Difficulty Level Selection

bool getDifficultyLevel(int& rows, int& cols, int& timelimit) {
    char choice;
    while (true) {
        cout << "Choose difficulty level:\n";
        cout << "  E - Easy (4x2, 4 pairs, 180 seconds)\n";
        cout << "  M - Medium (4x4, 8 pairs, 240 seconds)\n";
        cout << "  H - Hard (6x4, 12 pairs, 250 seconds)\n";
        cout << "  C - Customize\n";
        cout << "Enter E, M, H, or C: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = toupper(choice);

        if (choice == 'E') {
            rows = 4; cols = 2; timelimit = 180;
            return true;
        } else if (choice == 'M') {
            rows = 4; cols = 4; timelimit = 240;
            return true;
        } else if (choice == 'H') {
            rows = 6; cols = 4; timelimit = 250;
            return true;
        } else if (choice == 'C') {
            cout << "Enter number of rows: ";
            cin >> rows;
            cout << "Enter number of columns: ";
            cin >> cols;
            cout << "Enter time limit (seconds): ";
            cin >> timelimit;
            return true;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

// 7. Fisher Yates Algorithm 
// Randomized fruit pools

void fisherYatesShuffle(vector<string>& vec) {
    srand(static_cast<unsigned int>(time(0)));
    for (size_t i = vec.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);
        swap(vec[i], vec[j]);
    }
}
