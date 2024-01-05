//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_CHESSBOARD_H
#define AI_BACKGAMMON_CHESSBOARD_H

#include "GameObject.h"

class ChessBoard : public GameObject {
public:

    ChessBoard();

    void Draw() override;

    Event Update() override;

    static Coord getMouseCoord();
};


#endif //AI_BACKGAMMON_CHESSBOARD_H
