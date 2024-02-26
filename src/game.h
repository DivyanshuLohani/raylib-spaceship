#pragma once
#include <raylib.h>
#include "spaceship.h"

class Game
{
public:
    void Draw();
    void Update();

private:
    Spaceship m_player;
};