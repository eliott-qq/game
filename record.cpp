#include "record.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

// 1. Sort Gameplay Difficulty

int difficultyRank(const string& difficulty) {
    if (difficulty == "Easy") return 1;
    if (difficulty == "Medium") return 2;
    if (difficulty == "Hard") return 3;
    return 4; // Custom
}

// 2. Sorting Gameplay Records
// The new record is inserted based on the difficulty level and time spent

void insertSorted(GameRecord*& head, GameRecord* newRecord) {
    if (!head || difficultyRank(newRecord->difficulty) < difficultyRank(head->difficulty) ||
        (difficultyRank(newRecord->difficulty) == difficultyRank(head->difficulty) && newRecord->timeSpent < head->timeSpent)) {
        newRecord->next = head;
        head = newRecord;
        return;
    }
    GameRecord* curr = head;
    while (curr->next &&
          (difficultyRank(newRecord->difficulty) > difficultyRank(curr->next->difficulty) ||
          (difficultyRank(newRecord->difficulty) == difficultyRank(curr->next->difficulty) && newRecord->timeSpent > curr->next->timeSpent))) {
        curr = curr->next;
    }
    newRecord->next = curr->next;
    curr->next = newRecord;
}
// 3. Print Game Records
// Print the game records in a sorted order

void printRecords(GameRecord* head) {
    cout << "\n=== Game History ===\n";
    if (!head) {
        cout << "No past records.\n";
        return;
    }
    GameRecord* curr = head;
    int count = 1;
    while (curr) {
        cout << count++ << ". " << curr->difficulty << " | "
             << fixed << setprecision(2) << curr->timeSpent << "s | "
             << curr->timestamp << endl;
        curr = curr->next;
    }
}

// 4. Save New Gameplay
// The records are saved in a text file named "records.txt"

void saveRecords(GameRecord* head) {
    ofstream outFile("records.txt");
    GameRecord* curr = head;
    while (curr) {
        outFile << curr->difficulty << "," << curr->timeSpent << "," << curr->timestamp << "\n";
        curr = curr->next;
    }
}

// 5. Load Saved Gameplay
// Load game records from "records.txt" file

void loadRecords(GameRecord*& head) {
    ifstream inFile("records.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string diff, timeStr, timestamp;
        getline(iss, diff, ',');
        getline(iss, timeStr, ',');
        getline(iss, timestamp);

        GameRecord* newRecord = new GameRecord{diff, stod(timeStr), timestamp, nullptr};
        insertSorted(head, newRecord);
    }
}

// 6. Gameplay Timestamp
// Get the current timestamp formatted as YYYY-MM-DD HH:MM:SS

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << 1900 + ltm->tm_year << "-"
       << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    return ss.str();
}

// 7. Delete All Gameplay Records
// Option to delete all gameplay records

void deleteAllRecords(GameRecord*& head) {
    while (head) {
        GameRecord* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    saveRecords(head);  // Update the records file to be empty
    cout << "All records have been deleted." << endl;
}

