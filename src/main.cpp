#include <raylib.h>
#include "game.h"
#include "enemy.h"
int main()
{
    const int screenWidth = 750;
    const int screenHeight = 800;
    Color background = {17, 14, 26, 255};

    InitWindow(screenWidth, screenHeight, "Spaceship");
    InitAudioDevice();
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.Update();
        BeginDrawing();
        ClearBackground(background);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}