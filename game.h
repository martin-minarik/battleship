#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "tile_map_management.h"

typedef struct InitVariables {
    short int shipCount;
    short int sizeOfField;
} InitVariables;

typedef struct Score {
    short int hitCount;
    short int missCount;
} Score;

void setup(TileOfField field[][15], int shipCount, int sideOfField);

char input(Vector2i *player_position, TileOfField *tile, int sideOfField, Score *score);

void printHint(Score *score, int shipCount);

void printRemainingTime(const time_t *gameTime);

void printScoreToFile(Score *score, InitVariables *initValues,
                      const time_t *gameTime);

void runGame(InitVariables *initValues);

#endif // GAME_H
