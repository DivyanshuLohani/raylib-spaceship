#include <raylib.h>
#include "spaceship.h"
#include "lazer.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    Color background = {17, 14, 26, 255};

    InitWindow(screenWidth, screenHeight, "Spaceship");
    SetTargetFPS(60);

    Spaceship spaceship;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(background);
        spaceship.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}