//
// Created by Cyril on 2023/12/9.
//

#ifndef AI_BACKGAMMON_EVENTMANAGER_H
#define AI_BACKGAMMON_EVENTMANAGER_H

#include <queue>
#include "Event.h"

class EventManager {
public:
    static void Update();

    static void AddEvent(Event event);

    static bool IsGaming();

private:
    static void cancelOneStep();

    static void downOneStep(Coord coord);

    static void loadState();

private:
    static bool IS_GAME_OVER;

    static bool IS_GAMING;

    static priority_queue <Event> m_eventQueue;
};


#endif //AI_BACKGAMMON_EVENTMANAGER_H
