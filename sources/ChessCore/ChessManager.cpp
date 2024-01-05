//
// Created by Cyril on 2023/11/24.
//

#include <cassert>
#include <cstring>
#include "ChessManager.h"

int ChessManager::computerIsPWhat = COMPUTER_P_WHAT;

int ChessManager::m_map[16][16]{};

int ChessManager::m_chessNum = 0;

std::stack<Coord> ChessManager::m_stackCoord;

ChessManager::ChessManager() {
    ChessEngine::initMap(m_map);
}

void ChessManager::downOneStep(Coord coord) {
    assert(m_map[coord.x][coord.y] == NO_CHESS);//我断言这里没有棋子
    m_stackCoord.push(coord);//记录下的子
    m_map[coord.x][coord.y] = isBlackDownNow() ? BLACK_CHESS : WHITE_CHESS;//选了一个颜色
    m_chessNum++;//下了
}

//返回：现在是轮到黑下了吗？
bool ChessManager::isBlackDownNow() {
    return isP1Turn();//默认是先手黑棋
}

bool ChessManager::isBlackDownPrev() {
    return not isBlackDownNow();
}

void ChessManager::cancelOneStep() {
    Coord coord = m_stackCoord.top();
    assert(m_map[coord.x][coord.y] != NO_CHESS);//我断言这里有棋子
    m_stackCoord.pop();
    m_map[coord.x][coord.y] = NO_CHESS;
    m_chessNum--;
}

void ChessManager::switchPlayer() {
    if (computerIsPWhat == 1) {
        computerIsPWhat = 2;
        return;
    }
    if (computerIsPWhat == 2) {
        computerIsPWhat = 1;
        return;
    }
}

bool ChessManager::isComputerNow() {
    if (computerIsPWhat == 1) return isP1Turn();
    if (computerIsPWhat == 2) return isP2Turn();
    return false;
}

bool ChessManager::isP1Turn() {
    return m_chessNum % 2 == 0;//没有子的时候就是轮到p1的时候了 加2同理
}

bool ChessManager::isP2Turn() {
    return not isP1Turn();
}

bool ChessManager::isValidInMap(Coord coord) {
    return m_map[coord.x][coord.y] == NO_CHESS;
}

bool ChessManager::thereIsNoComputer() {
    return computerIsPWhat == 0;
}

bool ChessManager::noChessCanDown() {
    return m_chessNum == 15 * 15;
}

Coord ChessManager::getMaxCoord() {
    return ChessEngine::getMaxCoord();
}

bool ChessManager::someoneWin(Coord lastDownCoord) {
    return ChessEngine::someoneWin(lastDownCoord);
}

Event ChessManager::update() {
    if (noChessCanDown()) {
        return EVENT_IS_DRAW;
    }
    if (!m_stackCoord.empty() and someoneWin(m_stackCoord.top())) {
        return isP1Turn() ? EVENT_IS_P2_WIN : EVENT_IS_P1_WIN;
    }
    if (isComputerNow()) {
        return EVENT_IS_COMPUTER_DOWN_ONE_STEP;
    }
    return EVENT_NONE;
}

void ChessManager::init() {
    ChessEngine::initMap(m_map);
}

void ChessManager::clear() {
    while (!m_stackCoord.empty()) {
        m_stackCoord.pop();
    }
    m_chessNum = 0;
    memset(m_map, 0, sizeof(m_map));
}

void ChessManager::saveState() {
    fstream file("save.txt", ios::out);
    //如果有人赢了就不存储了
    if (!m_stackCoord.empty() and someoneWin(m_stackCoord.top())) {
        return;
    }
    while (!m_stackCoord.empty()) {
        Coord coord = m_stackCoord.top();
        file << coord.x << " " << coord.y << endl;
        m_stackCoord.pop();
    }
    file.close();
}
