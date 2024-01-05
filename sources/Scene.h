//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_SCENE_H
#define AI_BACKGAMMON_SCENE_H


#include <list>
#include "Object/GameObject.h"
#include "General/General.h"
#include "ChessCore/ChessManager.h"
#include "ChessCore/ChessEngine.h"


class Scene {
private:
    Scene();

public:
    Scene(const Scene &) = delete;

    Scene &operator=(const Scene &) = delete;

    ~Scene();

    static void Update();

    static void Draw();

    static void AddObject(GameObject *object);

    static void DeleteObject(GAME_OBJECT_ID id);

public:
    typedef std::list<GameObject *> ObjectPool;

    static ObjectPool m_gameObjects;
};


#endif //AI_BACKGAMMON_SCENE_H
