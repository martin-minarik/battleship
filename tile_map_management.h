#ifndef TILE_MAP_MANAGEMENT_H
#define TILE_MAP_MANAGEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_SIDE 15
typedef struct TileOfField
{
    char appearance;
    short int type;

} TileOfField;

typedef struct Vector2i
{
    int x;
    int y;
} Vector2i;

enum {
    ALIVE, HIT, MISS, WATER
};

enum {
    DEFAULT_COLOR = 7,
    FG_WHITE = 15,
    FG_CYAN = 11,
    FG_RED = 12,
    FG_BG_BLACK_RED = 192,
    FG_BG_BLACK_CYAN = 176,
    FG_BG_BLACK_YELLOW = 224,
    FG_BG_BLACK_WHITE = 240
};

Vector2i randomVector2i(int max);
void setConsoleColor(int i);
int getColorOfTile(TileOfField *tile);
void fillField(TileOfField field[][MAX_SIDE], int sideOfField);
void addShip(TileOfField field[][MAX_SIDE], int sideOfField);
char checkHit(TileOfField *tile);
void drawTileMap(TileOfField field[][MAX_SIDE], Vector2i *player_position, int sideOfField);

#endif // TILE_MAP_MANAGEMENT_H
