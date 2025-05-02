#include "fruitpool.h"
using namespace std;

// Fruit Pool: All the possible combinations of fruits

vector<string> fruitNames = {
    "Apple", "Banana", "Cherry", "Grape", "Watermelon",
    "Pineapple", "Kiwi", "Peach", "Strawberry", "Melon",
    "Mango", "Pear", "Orange", "Lemon", "GreenApple",
    "Tomato", "Eggplant", "Coconut", "Avocado"
};

// The colors of the fruits
// The colors are represented using ANSI escape codes

map<string, string> fruitColors = {
    {"Apple", "\033[31m"},
    {"Banana", "\033[33m"},
    {"Cherry", "\033[31m"},
    {"Grape", "\033[35m"},
    {"Watermelon", "\033[32m"},
    {"Pineapple", "\033[33m"},
    {"Kiwi", "\033[32m"},
    {"Peach", "\033[35m"},
    {"Strawberry", "\033[31m"},
    {"Melon", "\033[32m"},
    {"Mango", "\033[33m"},
    {"Pear", "\033[32m"},
    {"Orange", "\033[33m"},
    {"Lemon", "\033[33m"},
    {"GreenApple", "\033[32m"},
    {"Tomato", "\033[31m"},
    {"Eggplant", "\033[35m"},
    {"Coconut", "\033[37m"},
    {"Avocado", "\033[32m"}
};
