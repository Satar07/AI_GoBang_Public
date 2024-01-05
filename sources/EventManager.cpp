//
// Created by Cyril on 2023/12/9.
//
#include "General/General.h"
#include "Event.h"
#include "EventManager.h"
#include "ChessCore/ChessManager.h"
#include "Scene.h"
#include "Object/highLightChess.h"
#include "Object/Message.h"
#include "Object/ChessBoard.h"
#include "Object/UI.h"

priority_queue<Event> EventManager::m_eventQueue;

bool EventManager::IS_GAME_OVER = false;

bool EventManager::IS_GAMING = false;

void EventManager::Update() {
    while (!m_eventQueue.empty()) {
        Event event = m_eventQueue.top();
        m_eventQueue.pop();
        switch (event) {
            case EVENT_IS_WANT_TO_CANCEL:
                cancelOneStep();
                if (!ChessManager::thereIsNoComputer()) {
                    cancelOneStep();//人机对战模式撤回两次
                }
                break;
            case EVENT_IS_WANT_TO_SWITCH_PLAYER:
                ChessManager::switchPlayer();
                break;
            case EVENT_IS_DRAW:
                if (!IS_GAME_OVER) {
                    Scene::AddObject(new Message(" Draw!!"));
                }
                IS_GAME_OVER = true;
                break;
            case EVENT_IS_P1_WIN:
                if (!IS_GAME_OVER) {
                    Scene::AddObject(new Message("P1 Win!!"));
                }
                IS_GAME_OVER = true;
                break;
            case EVENT_IS_P2_WIN:
                if (!IS_GAME_OVER) {
                    Scene::AddObject(new Message("P2 Win!!"));
                }
                IS_GAME_OVER = true;
                break;
            case EVENT_IS_COMPUTER_DOWN_ONE_STEP:
                downOneStep(ChessManager::getMaxCoord());
                break;
            case EVENT_IS_HUMAN_WANT_TO_PLACE_CHESS:
                downOneStep(changeRawCoordToStander(GetMousePosition()));
                break;
            case EVENT_IS_WANT_TO_START:
                IS_GAMING = true;
                Scene::AddObject(new ChessBoard());
                break;
            case EVENT_IS_WANT_TO_RESUME:
                IS_GAMING = true;
                Scene::AddObject(new ChessBoard());
                loadState();
                break;
            case EVENT_SET_DIFFICULTY_LOW:
                ChessEngine::searchFloor = 3;
                break;
            case EVENT_SET_DIFFICULTY_MEDIUM:
                ChessEngine::searchFloor = 5;
                break;
            case EVENT_SET_DIFFICULTY_HIGH:
                ChessEngine::searchFloor = 7;
                break;
            case EVENT_SET_GAME_MODE_AI_FIRST:
                ChessManager::computerIsPWhat = 1;
                break;
            case EVENT_SET_GAME_MODE_AI_SECOND:
                ChessManager::computerIsPWhat = 2;
                break;
            case EVENT_SET_GAME_MODE_NO_AI:
                ChessManager::computerIsPWhat = 0;
                break;
            case EVENT_IS_WANT_TO_RETURN_TO_MAIN_MENU:
                ChessEngine::searchFloor = 3;
                ChessManager::computerIsPWhat = 1;
                IS_GAMING = false;
                IS_GAME_OVER = false;
                Scene::m_gameObjects.clear();
                Scene::AddObject(new UI);
                ChessManager::saveState();
                ChessManager::clear();
                break;
            case EVENT_NONE:
                break;
        }
    }
}

void EventManager::AddEvent(Event event) {
    if (event == Event::EVENT_NONE) {
        return;
    }
    m_eventQueue.push(event);

}

void EventManager::cancelOneStep() {
    if (IS_GAME_OVER) {
        IS_GAME_OVER = false;
        Scene::DeleteObject(MESSAGE_ID);
    }

    if (ChessManager::m_chessNum == 0)return;
    Scene::DeleteObject(GAME_OBJECT_ID::CHESS_ID);
    Scene::DeleteObject(GAME_OBJECT_ID::HIGHLIGHT_CHESS_ID);
    ChessManager::cancelOneStep();
    if (ChessManager::m_chessNum == 0) {
        Scene::DeleteObject(CHESS_ID);
        return;
    }
    //撤销恢复highlight
    auto *chess = new Chess(ChessManager::m_stackCoord.top(),
                            ChessManager::isBlackDownPrev());
    Scene::DeleteObject(CHESS_ID);
    Scene::AddObject(new highLightChess(chess));
    Scene::AddObject(chess);
}

void EventManager::downOneStep(Coord coord) {
    if (IS_GAME_OVER) return;
    if (!ChessManager::isValidInMap(coord)) return;
    ChessManager::downOneStep(coord);
    auto *chess = new Chess(coord, ChessManager::isBlackDownPrev());
    Scene::DeleteObject(HIGHLIGHT_CHESS_ID);
    Scene::AddObject(new highLightChess(chess));
    Scene::AddObject(chess);
}

bool EventManager::IsGaming() {
    return IS_GAMING;
}

void EventManager::loadState() {
    fstream file("save.txt", ios::in);
    if (!file) {
        return;
    }
    ChessManager::clear();
    int x, y;
    while (file >> x >> y) {
        downOneStep({x, y});
    }
    file.close();
}
