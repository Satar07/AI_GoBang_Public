//
// Created by Cyril on 2023/11/7.
//

#ifndef AI_BACKGAMMON_APPLICATION_H
#define AI_BACKGAMMON_APPLICATION_H

#include "raylib.h"
#include "Scene.h"

#define WINDOW_TITLE "Back Gammon"

class Application {
private:
    Application() = default;

public:
    Application(const Application &) = delete;

    Application &operator=(const Application &) = delete;

    static int main();

    static void WindowsInit();

    static void WindowsExist();

    static void core();
};


#endif //AI_BACKGAMMON_APPLICATION_H
