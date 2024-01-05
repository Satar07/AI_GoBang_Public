//
// Created by Cyril on 2023/11/7.
//

#include "Application.h"
#include "Object/UI.h"
#include "Object/ChessBoard.h"
#include "raygui.h"

int Application::main() {
    PROFILE_FUNCTION
    WindowsInit();
    core();
    WindowsExist();
    return 0;
}

void Application::core() {
    PROFILE_FUNCTION
    ChessManager::init();

    Scene::AddObject(new UI);
    //Scene::AddObject(new ChessBoard);

    while (!WindowShouldClose()) {
        Scene::Update();
        BeginDrawing();
        Scene::Draw();
        EndDrawing();
    }

}

void Application::WindowsInit() {
    PROFILE_FUNCTION
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);
    Image icon = LoadImage(ASSETS_PATH"icon.png");
    SetWindowIcon(icon);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 23);
}

void Application::WindowsExist() {
    PROFILE_FUNCTION
    CloseWindow();
}
