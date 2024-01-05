//
// Created by Cyril on 2023/11/24.
//

#include <cstring>
#include <algorithm>
#include <random>
#include "ChessEngine.h"

ChessEngine::ChessEngine() = default;

int ChessEngine::searchFloor = SEARCH_FLOOR;

ACEngine ChessEngine::blackEngine = {
        {"11111",  50000},
        {"011110", 4320},
        {"011100", 720},
        {"001110", 720},
        {"011010", 720},
        {"010110", 720},
        {"11110",  720},
        {"01111",  720},
        {"11011",  720},
        {"10111",  720},
        {"11101",  720},
        {"001100", 120},
        {"001010", 120},
        {"010100", 120},
        {"000100", 20},
        {"001000", 20},
};

ACEngine ChessEngine::whiteEngine = {
        {"22222",  50000},
        {"022220", 4320},
        {"022200", 720},
        {"002220", 720},
        {"022020", 720},
        {"020220", 720},
        {"22220",  720},
        {"02222",  720},
        {"22022",  720},
        {"20222",  720},
        {"22202",  720},
        {"002200", 120},
        {"002020", 120},
        {"020200", 120},
        {"000200", 20},
        {"002000", 20},};

int (*ChessEngine::m_map)[16] = nullptr;

void ChessEngine::initMap(int (*map)[16]) {
    m_map = map;
}

Coord ChessEngine::getMaxCoord() {
    PROFILE_FUNCTION
    Coord ret{};
    if (isNoChessDown()) {
        return {8, 8};
    }
    bool blackNow = isBlackNow();
    abSearch(searchFloor, -SEARCH_INFINITY, SEARCH_INFINITY, blackNow, ret);
    return ret;
}

//意义：目前棋盘的最值评分 分数的正负取决于一开始的isBlackNow
int ChessEngine::abSearch(int floor, int alpha, int beta, bool isBlackNow, Coord &searchResult) {
    PROFILE_FUNCTION
    int tmpScore, moveCount = 0;
    Coord tempSearchResult{};
    std::vector<ScoreCoord> possibleMove = generatePossibleMove(isBlackNow);
    for (auto &now: possibleMove) {
        moveCount++;
        if (moveCount > 8) break; //只搜索前8个可能的落子点
        int x = now.coord.x, y = now.coord.y;
        m_map[x][y] = isBlackNow ? BLACK_CHESS : WHITE_CHESS;
        if (someoneWin({x, y})) {//如果有人赢了 必定是下这个子的人赢了
            searchResult = {x, y};
            tmpScore = evaluateAll(isBlackNow);//返回这个局面最高的得分，也就是赢局的分数
            m_map[x][y] = NO_CHESS;
            return tmpScore;
        }
        if (floor == 1) {//如果只看这一步子 那就是这一步子所有可能的得分中的最大值
            tmpScore = evaluateAll(isBlackNow);
            m_map[x][y] = NO_CHESS;
            if (tmpScore > alpha) {
                alpha = tmpScore;
                searchResult = {x, y};
            }
            continue;
        }
        tmpScore = -abSearch(floor - 1, -beta, -alpha, !isBlackNow, tempSearchResult);//不然得分就是我下了之后的对方的所能得到的最高分取负
        m_map[x][y] = NO_CHESS;
        if (tmpScore >= beta) {
            return beta;
        }
        if (tmpScore > alpha) {//取对方尽所有努力后得到最大值中的最小的一个 取负值后变成最大的一个
            alpha = tmpScore;
            searchResult = {x, y};
        }
    }
    return alpha;
}

std::vector<ScoreCoord> ChessEngine::generatePossibleMove(bool isBlackNow) {
    PROFILE_FUNCTION
    std::vector<ScoreCoord> ret;
    ret.reserve(225);
    for (int x = 1; x <= 15; ++x) {
        for (int y = 1; y <= 15; ++y) {
            if (thereIsNoChessNearby({x, y}))continue;
            if (m_map[x][y] != NO_CHESS)continue;
            int baseScore = evaluateOnePoint(isBlackNow, {x, y});//没有落子前的分数
            m_map[x][y] = isBlackNow ? BLACK_CHESS : WHITE_CHESS;
            int myScore = evaluateOnePoint(isBlackNow, {x, y});//我下这点我会得到的分数
            m_map[x][y] = isBlackNow ? WHITE_CHESS : BLACK_CHESS;
            int rivalScore = evaluateOnePoint(!isBlackNow, {x, y});//如果我不下这点则敌方会得到的分数
            m_map[x][y] = NO_CHESS;
            ret.push_back({(myScore - baseScore) + (rivalScore - (-baseScore)), {x, y}});//要让我获益最大 或者能让敌方获益最大的点下棋
        }
    }
    std::shuffle(ret.begin(), ret.end(), std::mt19937(std::random_device()()));
    std::sort(ret.begin(), ret.end(), [](const ScoreCoord &a, const ScoreCoord &b) {
        return a.score > b.score;
    });
    return ret;
}

bool ChessEngine::someoneWin(Coord coord) {
    PROFILE_FUNCTION
    return (checkByStep(coord, 0, 1) + checkByStep(coord, 0, -1) >= 4) or
           (checkByStep(coord, 1, 0) + checkByStep(coord, -1, 0) >= 4) or
           (checkByStep(coord, 1, 1) + checkByStep(coord, -1, -1) >= 4) or
           (checkByStep(coord, 1, -1) + checkByStep(coord, -1, 1) >= 4);
}

int ChessEngine::checkByStep(Coord now, int x_step, int y_step) {
    PROFILE_FUNCTION
    int cc = 0;
    auto origin = now;
    now.x += x_step;
    now.y += y_step;
    while (isOnBoard(now) and
           (m_map[now.x][now.y] == m_map[origin.x][origin.y])) {
        cc++;
        now.x += x_step;
        now.y += y_step;
    }
    return cc;
}

//评估整个棋盘 如果是黑棋返回黑棋的得分 如果是白棋返回白棋的得分
int ChessEngine::evaluateAll(bool isBlackNow) {
    PROFILE_FUNCTION
    int ret = 0;
    char line[50] = {};

    //竖向
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1, lineIndex = 0; j <= 15; ++j, lineIndex++) {
            line[lineIndex] = chessChar(m_map[i][j]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    //横向
    for (int j = 1; j <= 15; ++j) {
        for (int i = 1, lineIndex = 0; i <= 15; ++i, lineIndex++) {
            line[lineIndex] = chessChar(m_map[i][j]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    //右上到左下
    for (int i = 5; i <= 15; ++i) {
        memset(line, 0, sizeof line);
        for (int x = i, y = 1, lineIndex = 0; x >= 1; x--, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    for (int i = 2; i <= 11; ++i) {
        memset(line, 0, sizeof line);
        for (int x = 15, y = 15 + i - x, lineIndex = 0; y <= 15; x--, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    // 左上到右下
    for (int i = 10; i >= 0; --i) {
        memset(line, 0, sizeof line);
        for (int x = 1, y = x + i, lineIndex = 0; y <= 15; x++, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    for (int i = -1; i >= -10; --i) {
        memset(line, 0, sizeof line);
        for (int y = 1, x = y - i, lineIndex = 0; x <= 15; x++, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
        ret += getLineScore(line, isBlackNow);
    }
    return ret;
}

int ChessEngine::evaluateOnePoint(bool isBlackNow, Coord coord) {
    PROFILE_FUNCTION
    int ret = 0;
    char line[50] = {};
    //coord所在位置的横向
    for (int x = 1, lineIndex = 0; x <= 15; ++x, lineIndex++) {
        line[lineIndex] = chessChar(m_map[x][coord.y]);
    }
    ret += getLineScore(line, isBlackNow);
    //coord所在位置的竖向
    for (int y = 1, lineIndex = 0; y <= 15; ++y, lineIndex++) {
        line[lineIndex] = chessChar(m_map[coord.x][y]);
    }
    ret += getLineScore(line, isBlackNow);
    memset(line, 0, sizeof line);
    //coord所在位置的右上到左下
    //画图求函数解析式后得出算法
    int b = coord.x + coord.y;
    if (b <= 16) {
        for (int x = b - 1, y = 1, lineIndex = 0; x >= 1; x--, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
    } else {
        for (int x = 15, y = b - 15, lineIndex = 0; y <= 15; x--, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
    }
    ret += getLineScore(line, isBlackNow);
    memset(line, 0, sizeof line);
    //coord所在位置的左上到右下
    int a = coord.x - coord.y;
    if (a >= 0) {
        for (int x = a + 1, y = 1, lineIndex = 0; x <= 15; x++, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
    } else {
        for (int x = 1, y = -a + 1, lineIndex = 0; y <= 15; x++, y++, lineIndex++) {
            line[lineIndex] = chessChar(m_map[x][y]);
        }
    }
    ret += getLineScore(line, isBlackNow);
    return ret;
}

inline int ChessEngine::getLineScore(const char *line, bool isBlackNow) {
    PROFILE_FUNCTION
    return isBlackNow ?
           blackEngine.ACSearch(line) - whiteEngine.ACSearch(line) :
           -blackEngine.ACSearch(line) + whiteEngine.ACSearch(line);
}

bool ChessEngine::isBlackNow() {
    PROFILE_FUNCTION
    int blackCC = 0, whiteCC = 0;
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 15; ++j) {
            switch (m_map[i][j]) {
                case NO_CHESS:
                    continue;
                case WHITE_CHESS:
                    whiteCC++;
                    continue;
                case BLACK_CHESS:
                    blackCC++;
                    continue;
                default:
                    assert(false);
            }
        }
    }
    if (blackCC == whiteCC)return true;
    return false;
}

inline char ChessEngine::chessChar(int chessType) {
    switch (chessType) {
        case NO_CHESS:
            return '0';
        case WHITE_CHESS:
            return '2';
        case BLACK_CHESS:
            return '1';
        default:
            assert(false);
    }
}

//棋盘上没有棋子
bool ChessEngine::isNoChessDown() {
    PROFILE_FUNCTION
    for (int i = 1; i <= 15; ++i) {
        for (int j = 1; j <= 15; ++j) {
            if (m_map[i][j] != NO_CHESS)return false;
        }
    }
    return true;
}

inline bool ChessEngine::thereIsNoChessNearby(Coord coord) {
    for (int i = max(1, coord.x - 2); i <= min(15, coord.x + 2); ++i) {
        for (int j = max(1, coord.y - 2); j <= min(15, coord.y + 2); ++j) {
            if (m_map[i][j] != NO_CHESS)return false;
        }
    }
    return true;
}

