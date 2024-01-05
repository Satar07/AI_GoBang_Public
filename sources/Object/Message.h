//
// Created by Cyril on 2023/11/14.
//

#ifndef AI_BACKGAMMON_MESSAGE_H
#define AI_BACKGAMMON_MESSAGE_H

#include "GameObject.h"

class Message : public GameObject {
public:
    explicit Message(const char *message);

    void Draw() override;

    Event Update() override;

    char *m_message;

};


#endif //AI_BACKGAMMON_MESSAGE_H
