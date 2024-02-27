#include "enemy.h"

Texture2D Enemy::m_textures[3] = {};

Enemy::Enemy() {}

Enemy::Enemy(Enemytype type, Vector2 position)
{

    m_position = position;
    m_health = type;
    m_type = type;

    if (m_textures[type - 1].id != 0)
        return;

    switch (type)
    {
    case ALIEN_1:
        m_textures[0] = LoadTexture("Graphics/alien_1.png");
        break;
    case ALIEN_2:
        m_textures[1] = LoadTexture("Graphics/alien_2.png");
        break;
    case ALIEN_3:
        m_textures[2] = LoadTexture("Graphics/alien_3.png");
        break;

    default:
        m_textures[0] = LoadTexture("Graphics/alien_1.png");
        TraceLog(LOG_WARNING, "Enemy type not found %d", type);
        break;
    }
}

void Enemy::Draw()
{
    DrawTextureV(m_textures[m_type - 1], m_position, WHITE);
}

void Enemy::Update()
{
}

Texture2D Enemy::GetTexture()
{
    return m_textures[m_type - 1];
}
