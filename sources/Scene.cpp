//
// Created by Cyril on 2023/11/7.
//

#include "Scene.h"
#include "Object/Chess.h"
#include "General/General.h"
#include "EventManager.h"

Scene::ObjectPool Scene::m_gameObjects;

Scene::Scene() = default;

Scene::~Scene() = default;

void Scene::Draw() {
    PROFILE_FUNCTION
    for (GameObject *obj: m_gameObjects) {
        if (obj->m_isActive) {
            obj->Draw();
        }
    }
}

void Scene::AddObject(GameObject *object) {
    PROFILE_FUNCTION
    m_gameObjects.push_back(object);
}

void Scene::Update() {
    PROFILE_FUNCTION
    for (GameObject *obj: m_gameObjects) {
        if (obj->m_isActive) {
            EventManager::AddEvent(obj->Update());
        }
    }
    if (EventManager::IsGaming()) {
        EventManager::AddEvent(ChessManager::update());
    }
    EventManager::Update();
}


//从后往前删除
void Scene::DeleteObject(GAME_OBJECT_ID id) {
    PROFILE_FUNCTION
    for (auto it = m_gameObjects.rbegin(); it != m_gameObjects.rend(); it++) {
        if ((*it)->m_id == id) {
            m_gameObjects.erase((++it).base());
            return;
        }
    }
}
