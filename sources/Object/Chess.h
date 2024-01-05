//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_CHESS_H
#define AI_BACKGAMMON_CHESS_H

#include "GameObject.h"
#include "raylib.h"
#include "General/General.h"


//单个棋子的对象
class Chess : public GameObject {
public:
    Chess(Coord coord, bool IsBlack);

    void Draw() override;

    Event Update() override;

public:
    Coord m_standardCoord{};
    Vector2 m_realCoord{};
    Color m_color{};
};


#endif //AI_BACKGAMMON_CHESS_H
