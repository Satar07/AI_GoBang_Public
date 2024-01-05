//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_UI_H
#define AI_BACKGAMMON_UI_H

#include "Object/GameObject.h"

class UI : public GameObject {
public:
    UI();

    void Draw() override;

    Event Update() override;

private:
    int m_difficulty = 1;

    bool m_SpinnerEditMode = false;

    bool IS_GAMING = false;

    int m_GameMode = 0;
};

#endif //AI_BACKGAMMON_UI_H
