#pragma once
#include <raylib.h>
#include <iostream>

enum Enemytype
{
    ALIEN_1 = 1,
    ALIEN_2,
    ALIEN_3,
    MYSTRY,
};

class Enemy
{
public:
    Enemy();
    Enemy(Enemytype type, Vector2 position);
    Enemytype GetType() { return m_type; }
    void Draw();
    void Update();

    Vector2 m_position;
    static Texture2D m_textures[3];
    Texture2D GetTexture();

private:
    int m_health;
    Enemytype m_type;
};
