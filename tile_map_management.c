#include "tile_map_management.h"

Vector2i randomVector2i(int max) {
    Vector2i point;

    point.x = rand() % (max);
    point.y = rand() % (max);

    return point;
}

void setConsoleColor(int i) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

int getColorOfTile(TileOfField *tile) {

    switch (tile->type) {
        case ALIVE:
            return FG_CYAN;
            break;
        case HIT:
            return FG_BG_BLACK_RED;
            break;
        case MISS:
            return FG_BG_BLACK_CYAN;
            break;
        case WATER:
            return FG_CYAN;
            break;

    }
    return 223;
}

void fillField(TileOfField field[][MAX_SIDE], int sideOfField) {
    for (int j = 0; j < MAX_SIDE; ++j) {
        for (int i = 0; i < sideOfField; ++i) {
            field[i][j].appearance = '~';
            field[i][j].type = WATER;
        }
    }
}

void addShip(TileOfField field[][MAX_SIDE], int sideOfField) {
    Vector2i point;
    do {
        point = randomVector2i(sideOfField);
    } while (field[point.x][point.y].type != WATER);

    field[point.x][point.y].appearance = 'L';
    field[point.x][point.y].type = ALIVE;
}

char checkHit(TileOfField *tile) {
    switch (tile->type) {
        case ALIVE:

            tile->type = HIT;
            tile->appearance = '#';
            return 1;
            break;
        case WATER:
            tile->type = MISS;
            tile->appearance = '#';
            return 0;
            break;

    }
    return 0;
}

void drawTileMap(TileOfField field[][MAX_SIDE], Vector2i *player_position, int sideOfField) {
    printf("    ");
    for (int i = 0; i < sideOfField; ++i) {
        setConsoleColor(FG_WHITE);
        printf("%2d|", i);
    }

    printf("\n");
    for (int j = 0; j < sideOfField; ++j) {
        setConsoleColor(FG_WHITE);
        printf("%3d| ", j);
        for (int i = 0; i < sideOfField; ++i) {
            if (player_position->x == i && player_position->y == j) {
                setConsoleColor(FG_BG_BLACK_WHITE);
            } else setConsoleColor(getColorOfTile(&field[i][j]));

            if (field[i][j].type != ALIVE) {
                printf("%c", field[i][j].appearance);
            } else printf("~");

            setConsoleColor(DEFAULT_COLOR);
            printf("  ");

        }
        printf("\n");
    }

}
