#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "tile_map_management.h"
#include "game.h"

void printMenuOptions(char menuOptions[][40], int numberOfOptions, const int *index);

char menuOptionChoose(int *index, int numberOfOptions);

void menuOptionChooseLoop(char menuOptions[][40], int *index, int numberOfOptions);

void printScoreFromFile();

void menu1(InitVariables *initValues);

void menu2(InitVariables *initValues);

void menuInit(InitVariables *initValues);

#endif // MENU_H
