//
// Created by Cyril on 2023/11/7.
//

#include "UI.h"
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

void UI::Draw() {
    static Texture m_texture = LoadTexture(ASSETS_PATH"icon.png");
    ClearBackground(LIGHTGRAY);
    if (!IS_GAMING) {
        DrawTexture(m_texture, 410, 150, WHITE);
    }
}

UI::UI() {
    m_id = GAME_OBJECT_ID::UI_ID;
}

Event UI::Update() {
    int newDifficulty = m_difficulty;
    if (!IS_GAMING) {
        if (GuiButton((Rectangle) {360, 480, 300, 50}, "START")) {
            IS_GAMING = true;
            return Event::EVENT_IS_WANT_TO_START;
        }
        if (GuiButton((Rectangle) {360, 620, 300, 50}, "RESUME")) {
            IS_GAMING = true;
            return Event::EVENT_IS_WANT_TO_RESUME;
        }
        if (GuiSpinner((Rectangle) {360, 760, 300, 50}, "DIFFICULTY (1~3) ",
                       &newDifficulty, 1, 3, m_SpinnerEditMode)) {
            m_SpinnerEditMode = !m_SpinnerEditMode;
        }
        if (newDifficulty != m_difficulty) {
            m_difficulty = newDifficulty;
            switch (newDifficulty) {
                case 1:
                    return Event::EVENT_SET_DIFFICULTY_LOW;
                case 2:
                    return Event::EVENT_SET_DIFFICULTY_MEDIUM;
                case 3:
                    return Event::EVENT_SET_DIFFICULTY_HIGH;
                default:
                    return Event::EVENT_NONE;
            }
        }
        int new_GameMode = m_GameMode;
        GuiToggleGroup((Rectangle) {360, 890, 100, 50},
                       "AI fir;AI sec;NO AI", &new_GameMode);
        if (m_GameMode != new_GameMode) {
            m_GameMode = new_GameMode;
            switch (m_GameMode) {
                case 0:
                    return Event::EVENT_SET_GAME_MODE_AI_FIRST;
                case 1:
                    return Event::EVENT_SET_GAME_MODE_AI_SECOND;
                case 2:
                    return Event::EVENT_SET_GAME_MODE_NO_AI;
                default:
                    return Event::EVENT_NONE;
            }
        }
        return Event::EVENT_NONE;
    }//IS NOT GAMING BELOW

    if (GuiButton((Rectangle) {10, 10, 50, 50}, "<")) {
        IS_GAMING = false;
        m_difficulty = 1;
        m_GameMode = 0;
        return Event::EVENT_IS_WANT_TO_RETURN_TO_MAIN_MENU;
    }

    if (IsKeyPressed(KEY_LEFT)) {
        return Event::EVENT_IS_WANT_TO_CANCEL;
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        return Event::EVENT_IS_WANT_TO_SWITCH_PLAYER;
    }
    return Event::EVENT_NONE;
}



