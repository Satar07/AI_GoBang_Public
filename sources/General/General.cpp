//
// Created by Cyril on 2023/11/24.
//
#include "General.h"
#include <cmath>

Coord changeRawCoordToStander(Vector2 raw) {
    return {static_cast<int>(round((raw.x - BOARD_X) / (static_cast<float>(BOARD_WIDTH) / 16))),
            static_cast<int>(round((raw.y - BOARD_Y) / (static_cast<float>(BOARD_HEIGHT) / 16)))};
}

bool isOnBoard(Coord coord) {
    return coord.x > 0 and coord.x < 16 and coord.y > 0 and coord.y < 16;
}

Vector2 changeStanderCoordToRaw(Coord standard) {
    return {static_cast<float>(standard.x * (static_cast<double>(BOARD_WIDTH) / 16)) + BOARD_X,
            static_cast<float>(standard.y * (static_cast<double>(BOARD_HEIGHT) / 16)) + BOARD_Y};
}