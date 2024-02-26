#pragma once
#include <raylib.h>

class Spaceship
{

public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void Update();

private:
    Vector2 m_position;
    int m_health;
    Texture2D m_texture;
};