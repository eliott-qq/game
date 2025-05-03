#ifndef GAME_H
#define GAME_H

#include "record.h"
extern GameRecord* recordHead;

void runProgram(bool loadSaved = false);
bool shouldRestart();

#endif