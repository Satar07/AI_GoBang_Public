//
// Created by Cyril on 2023/11/24.
//

#ifndef AI_BACKGAMMON_CHESSMANAGER_H
#define AI_BACKGAMMON_CHESSMANAGER_H

#define COMPUTER_P_WHAT 1

#include <stack>
#include "General/General.h"
#include "ChessEngine.h"
#include "Event.h"

class ChessManager {
private:
    ChessManager();

public:
    ChessManager(const ChessManager &) = delete;

    ChessManager &operator=(const ChessManager &) = delete;

    static void init();

    static bool isBlackDownNow();

    static bool isBlackDownPrev();

    static void cancelOneStep();

    static void switchPlayer();

    static bool isComputerNow();

    static void downOneStep(Coord coord);

    static bool isP1Turn();

    static bool isP2Turn();

    static bool thereIsNoComputer();

    static bool isValidInMap(Coord coord);

    static bool noChessCanDown();

    static Coord getMaxCoord();

    static bool someoneWin(Coord lastDownCoord);

    static Event update();

    static void clear();

    static void saveState();

public:
    //[横坐标→][纵坐标↓] 坐标边界1开始15结束 0--NO_CHESS
    static int m_map[16][16];

    static std::stack<Coord> m_stackCoord;

    //总共下棋的个数
    //从0开始 单数是P1下 双数是P2下
    static int m_chessNum;

    //电脑是P几 默认是1 即先手 如果是0则没有电脑参与
    static int computerIsPWhat;
};


#endif //AI_BACKGAMMON_CHESSMANAGER_H
