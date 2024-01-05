//
// Created by Cyril on 2023/11/14.
//

#ifndef AI_BACKGAMMON_GENERAL_H
#define AI_BACKGAMMON_GENERAL_H

#include "raylib.h"
#include <cassert>

#include "BenchMark.h"

#define SCREEN_WIDTH (1000)
#define SCREEN_HEIGHT (1200)
#define BOARD_WIDTH 1000
#define BOARD_HEIGHT 1000
#define BOARD_X 0
#define BOARD_Y 50

#define SEARCH_INFINITY 1000000000

enum {
    NO_CHESS = 0, BLACK_CHESS = 1, WHITE_CHESS = 2
};

enum GAME_OBJECT_ID {
    CHESS_ID,
    CHESS_BOARD_ID,
    MESSAGE_ID,
    UI_ID,
    HIGHLIGHT_CHESS_ID,
};

struct Coord {
    int x, y;
};

Coord changeRawCoordToStander(Vector2 raw);

bool isOnBoard(Coord coord);

Vector2 changeStanderCoordToRaw(Coord standard);

#endif //AI_BACKGAMMON_GENERAL_H
