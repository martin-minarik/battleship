#include "game.h"

void setup(TileOfField field[][15], int shipCount, int sideOfField) {
    srand((unsigned) time(NULL));

    fillField(field, sideOfField);

    for (int i = 0; i < shipCount; ++i) {
        addShip(field, sideOfField);
    }
}

char input(Vector2i *player_position, TileOfField *tile, int sideOfField, Score *score) {

    if ((GetAsyncKeyState(VK_RETURN) & 0x8000) && ((tile->type != HIT) || (tile->type != MISS))) {
        if (checkHit(tile)) {
            score->hitCount += 1;
        } else {
            score->missCount += 1;
        }

        return 1;
    } else if (GetAsyncKeyState(VK_LEFT) && player_position->x != 0) {
        player_position->x--;
        return 1;
    } else if (GetAsyncKeyState(VK_UP) && player_position->y != 0) {
        player_position->y--;
        return 1;
    } else if (GetAsyncKeyState(VK_RIGHT) && player_position->x != sideOfField - 1) {
        player_position->x++;
        return 1;
    } else if (GetAsyncKeyState(VK_DOWN) && player_position->y != sideOfField - 1) {
        player_position->y++;
        return 1;
    }
    return 0;
}

void printHint(Score *score, int shipCount) {

    for (int i = 0; i < 60; ++i) {
        printf("_");
    }
    setConsoleColor(FG_WHITE);
    printf("\nHit: ");
    setConsoleColor(DEFAULT_COLOR);
    printf("%d, ", score->hitCount);

    setConsoleColor(FG_WHITE);
    printf("Missed: ");
    setConsoleColor(DEFAULT_COLOR);
    printf("%d, ", score->missCount);

    setConsoleColor(FG_WHITE);
    printf("Ships remaining: ");
    setConsoleColor(DEFAULT_COLOR);
    printf("%d\n", shipCount - score->hitCount);

    setConsoleColor(FG_BG_BLACK_YELLOW);
    printf("Control keys:"
           "\n\"Escape\" -> Exit,"
           "\n\"LEFT ARROW\" -> Move Left,"
           "\n\"UP ARROW\" -> Move Up,"
           "\n\"RIGHT ARROW\" -> Move Right,"
           "\n\"DOWN ARROW\" -> Move Down,"
           "\n\"Enter\" -> Hit");
    setConsoleColor(DEFAULT_COLOR);
    printf("\n");
    setConsoleColor(FG_WHITE);
    printf("Elapsed time:\n");
    setConsoleColor(DEFAULT_COLOR);
}

void printRemainingTime(const time_t *gameTime) {

    printf("%ds", (int) (time(NULL) - *gameTime));
}

void printScoreToFile(Score *score, InitVariables *initValues, const time_t *gameTime) {
    FILE *file;
    file = fopen("last_results.txt", "w");
    if (file == NULL) {
        printf("\nFile cannot be opened\n");
        system("pause");
        exit(1);
    }
    if (initValues->shipCount - score->hitCount == 0) {
        fprintf(file, "VICTORY!\n");
    } else fprintf(file, "DEFEAT!\n");
    fprintf(file, "Succesful hits: %d/%d, Missed hits: %d/%d, Ships: %d/%d Elapsed time: %ds",
            score->hitCount, score->hitCount + score->missCount, score->missCount, score->hitCount + score->missCount,
            initValues->shipCount - score->hitCount, initValues->shipCount, (int) (time(NULL) - *gameTime));

    if (fclose(file) == EOF) {

        printf("\nFile cannot be closed\n");
        system("pause");
        exit(1);
    }


}

void runGame(InitVariables *initValues) {
    TileOfField enemy_field[initValues->sizeOfField][MAX_SIDE];
    Score score = {0, 0};
    Vector2i player_position = {0, 0};
    time_t gameTime;
    time(&gameTime);

    setup(enemy_field, initValues->shipCount, initValues->sizeOfField);


    drawTileMap(enemy_field, &player_position, initValues->sizeOfField);
    printHint(&score, initValues->shipCount);
    printRemainingTime(&gameTime);

    while (!GetAsyncKeyState(VK_ESCAPE) && score.hitCount != initValues->shipCount) {
        if (_kbhit()) {
            getch();
            if (input(&player_position, &enemy_field[player_position.x][player_position.y], initValues->sizeOfField,
                      &score)) {
                system("cls");
                drawTileMap(enemy_field, &player_position, initValues->sizeOfField);
                printHint(&score, initValues->shipCount);
            }

        }

        printf("\r");
        printRemainingTime(&gameTime);

        Sleep(20);
    }

    system("cls");

    printScoreToFile(&score, initValues, &gameTime);

    setConsoleColor(FG_WHITE);

    if (initValues->shipCount - score.hitCount == 0) {
        printf("VICTORY!\n");

    } else printf("DEFEAT!\n");


    printf("Your results are saved to: \"last_results.txt\"");
    printf("\nSuccesful hits: %d/%d, Missed hits: %d/%d, Ships: %d/%d Elapsed time: %ds\n",
           score.hitCount, score.hitCount + score.missCount, score.missCount, score.hitCount + score.missCount,
           initValues->shipCount - score.hitCount, initValues->shipCount, (int) (time(NULL) - gameTime));

    setConsoleColor(DEFAULT_COLOR);

    system("pause");
}
