//
// Created by Cyril on 2023/11/7.
//

#include "ChessBoard.h"
#include "raylib.h"


void ChessBoard::Draw() {
    for (int i = 1; i < 16; ++i) {
        DrawLineEx(changeStanderCoordToRaw({1, i}),
                   changeStanderCoordToRaw({15, i}), 3, GRAY);
    }
    for (int i = 1; i < 16; ++i) {
        DrawLineEx(changeStanderCoordToRaw({i, 1}),
                   changeStanderCoordToRaw({i, 15}), 3, GRAY);
    }
}

ChessBoard::ChessBoard() {
    m_id = GAME_OBJECT_ID::CHESS_BOARD_ID;
}

Event ChessBoard::Update() {
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) return EVENT_NONE;
    Coord coord = getMouseCoord();
    if (!isOnBoard(coord)) return EVENT_NONE;
    return EVENT_IS_HUMAN_WANT_TO_PLACE_CHESS;
}

Coord ChessBoard::getMouseCoord() {
    Vector2 rawCoord = GetMousePosition();
    Coord standardCoord = changeRawCoordToStander(rawCoord);
    return standardCoord;
}
