#pragma once
#include <raylib.h>

class Lazer
{
public:
    Lazer(Vector2 position, int speed);
    ~Lazer();
    void Draw();
    void Update();

    bool m_active;
    Vector2 m_position;

private:
    int m_speed;
};