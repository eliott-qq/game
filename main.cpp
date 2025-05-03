#include "game.h"
#include "utils.h"
#include <iostream>
using namespace std;

// Game Introduction

// Serves as the entry point for the Memory Puzzle Game, initializing the game, handling saved game options, and controlling the game loop until the user chooses to exit.
// The function takes no command-line arguments and reads user input directly from the console.
// Returns 0 to indicate successful program termination.

int main() {
    clearScreen();
    loadRecords(recordHead);
    cout << "Welcome to the Memory Puzzle Game!" << endl;

// Screen Display Options: Starting Game or Resuming Game

    do {
        bool loadSaved = false;
        if (hasSavedGame()) {
            char choice;
            while (true) {
                cout << "\nDo you want to:\n";
                cout << "  N - Start a new game\n";
                cout << "  R - Resume saved game\n";
                cout << "Enter N or R: ";
                cin >> choice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choice = toupper(choice);
                cout << endl;
                if (choice == 'R') {
                    loadSaved = true;
                    break;
                } else if (choice == 'N') {
                    break;
                } else {
                    cout << "Invalid choice. Please enter N or R.\n";
                }
            }
        }
        runProgram(loadSaved); // Game Function Initiated
    } while (shouldRestart());

    clearScreen();
    cout << "Program ended." << endl;
    return 0;
}
