//
// Created by Cyril on 2023/11/14.
//

#include "Message.h"
#include "raylib.h"

Message::Message(const char *message) {
    m_message = (char *) message;
    m_id = GAME_OBJECT_ID::MESSAGE_ID;
}

void Message::Draw() {
    DrawRectangle(500 - 100, 500 - 40, 200, 80, GOLD);
    DrawText(m_message, 500 - 70, 500 - 20, 40, BLACK);
}

Event Message::Update() {
    return EVENT_NONE;
}
