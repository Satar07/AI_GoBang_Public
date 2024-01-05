//
// Created by Cyril on 2023/12/7.
//

#ifndef AI_BACKGAMMON_HIGHLIGHTCHESS_H
#define AI_BACKGAMMON_HIGHLIGHTCHESS_H


#include "GameObject.h"
#include "Chess.h"

class highLightChess : public GameObject {
public:
    explicit highLightChess(Chess *chess);

    void Draw() override;

    Event Update() override;

public:
    Chess *m_chess;
};


#endif //AI_BACKGAMMON_HIGHLIGHTCHESS_H
