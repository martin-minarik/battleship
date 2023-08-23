#include "menu.h"

char menuOptionChoose(int *index, int numberOfOptions) {
    unsigned char testChar;

    testChar = getch();
    if (testChar == 0 || testChar == 0xE0) {
        testChar = getch();
        switch (testChar) {
            case 72: // arrow up
                if (*index != 0) {
                    *index -= 1;
                    return 1;
                }
                break;

            case 80: // arrow down
                if (*index != numberOfOptions - 1) {
                    *index += 1;
                    return 1;
                }
                break;
        }
    }


    return 0;
}

void menuOptionChooseLoop(char menuOptions[][40], int *index, int numberOfOptions) {
    printMenuOptions(menuOptions, numberOfOptions, index);

    while (!GetAsyncKeyState(VK_RETURN)) { // Enter key

        if (menuOptionChoose(index, numberOfOptions)) {
            system("cls");
            printMenuOptions(menuOptions, numberOfOptions, index);
        }

        Sleep(100);
    }
    system("cls");
}

void printMenuOptions(char menuOptions[][40], int numberOfOptions, const int *index) {
    printf("\n");
    for (int i = 0; i < numberOfOptions; ++i) {
        if (i == *index) {
            setConsoleColor(FG_CYAN);
            printf("%s\n", &menuOptions[i][0]);
            setConsoleColor(DEFAULT_COLOR);
        } else printf("%s\n", &menuOptions[i][0]);
    }
}

void printScoreFromFile() {
    FILE *file;
    char s;

    file = fopen("last_results.txt", "r");

    if (file == NULL) {
        printf("\nFile cannot be opened\n");
        system("pause");
        exit(1);
    }

    setConsoleColor(FG_WHITE);
    do {
        s = getc(file);
        printf("%c", s);
    } while (s != EOF);
    setConsoleColor(DEFAULT_COLOR);

    if (fclose(file) == EOF) {
        printf("\nFile cannot be closed\n");
        system("pause");
        exit(1);
    }

    printf("\n");
    system("pause");
}

void menu1(InitVariables *initValues) {
    int index = 0;
    char titles[][40] =
            {
                    "Play",
                    "Print last_results.txt",
                    "Exit"
            };

    menuOptionChooseLoop(titles, &index, 3);


    switch (index) {
        case 0:
            menu2(initValues);
            break;
        case 1:
            printScoreFromFile();
            break;
        case 2:
            exit(0);
            break;
    }
}

void menu2(InitVariables *initValues) {
    int n = 0;

    do {
        printf("Side of field(min: 1, max: 15): ");
        scanf("%d", &n);
        system("cls");
    } while (n < 1 || n > 15);
    initValues->sizeOfField = n;

    do {
        printf("Count of ships(min: 1, max: %d): ", initValues->sizeOfField * initValues->sizeOfField);
        scanf("%d", &n);
        system("cls");
    } while (n < 0 || n > (initValues->sizeOfField * initValues->sizeOfField));

    initValues->shipCount = n;

    runGame(initValues);
}


void menuInit(InitVariables *initValues) {
    menu1(initValues);
}
