#include "game.h"
#include "menu.h"

/*
Title: Battleship
Autor: Martin Minarik
Date: 6.6.2019
*/

int main() {

    InitVariables initValues = {
            10, // shipCount
            5, // sizeOfField
    };

    menuInit(&initValues);

    return 0;
}
