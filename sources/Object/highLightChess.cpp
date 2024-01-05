//
// Created by Cyril on 2023/12/7.
//

#include "highLightChess.h"

highLightChess::highLightChess(Chess *chess) : m_chess(chess) {
    m_id = GAME_OBJECT_ID::HIGHLIGHT_CHESS_ID;
}

void highLightChess::Draw() {
    DrawCircleV(m_chess->m_realCoord, 30, BLUE);
}

Event highLightChess::Update() {
    return EVENT_NONE;
}
