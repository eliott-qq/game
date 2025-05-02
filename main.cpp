#include "game.h"
#include "utils.h"
#include <iostream>
using namespace std;

// Game Introduction

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
