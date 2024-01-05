//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_GAMEOBJECT_H
#define AI_BACKGAMMON_GAMEOBJECT_H

#include "General/General.h"
#include "Event.h"

class GameObject {
public:
    virtual void Draw() = 0;

    virtual Event Update() = 0;

public:
    int m_id{};

    bool m_isActive = true;
};


#endif //AI_BACKGAMMON_GAMEOBJECT_H
