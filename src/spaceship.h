#pragma once
#include <raylib.h>
#include "lazer.h"
#include <vector>

class Spaceship
{

public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void Update();
    Texture2D &GetTexture() { return m_texture; };

    std::vector<Lazer> m_lazers;
    Vector2 m_position;
    Sound m_fireSound;

private:
    void FireLazer();
    void HandleInput();

    int m_health;
    Texture2D m_texture;

    int m_speed = 5;
    float m_lastFireTime = 0.0f;
};