//
// Created by Cyril on 2023/11/7.
//

#include "Chess.h"
#include "raylib.h"

void Chess::Draw() {
    DrawCircleV(m_realCoord, 27, m_color);
}

Chess::Chess(Coord coord, bool IsBlack) {
    m_standardCoord = coord;
    m_realCoord = changeStanderCoordToRaw(m_standardCoord);
    m_color = IsBlack ? BLACK : WHITE;
    m_id = GAME_OBJECT_ID::CHESS_ID;
}

Event Chess::Update() {
    return EVENT_NONE;
}


