#include "spaceship.h"

Spaceship::Spaceship()
{
    m_texture = LoadTexture("Graphics/spaceship.png");
    m_fireSound = LoadSound("Audio/fire.wav");
    m_position.x = (GetScreenWidth() - m_texture.width) / 2;
    m_position.y = (GetScreenHeight() - m_texture.height) - 80;
}

Spaceship::~Spaceship()
{
    UnloadTexture(m_texture);
}

void Spaceship::Draw()
{
    DrawTextureV(m_texture, m_position, WHITE);
}

void Spaceship::Update()
{
    HandleInput();
}

void Spaceship::HandleInput()
{
    // Left
    if (IsKeyDown(KEY_A))
    {
        m_position.x -= m_speed;
        if (m_position.x < 0)
        {
            m_position.x = 0;
        }
    }
    // Right
    else if (IsKeyDown(KEY_D))
    {
        m_position.x += m_speed;
        if (m_position.x > GetScreenWidth() - m_texture.width)
        {
            m_position.x = GetScreenWidth() - m_texture.width;
        }
    }

    // Fire
    if (IsKeyDown(KEY_SPACE))
        FireLazer();
}

void Spaceship::FireLazer()
{
    // 0.2f means a lazer will be fired after 200 miliseconds
    if (GetTime() - m_lastFireTime >= 0.2f)
    {
        // Fire
        Lazer n_lazer({m_position.x + m_texture.width / 2, m_position.y}, 5);
        m_lazers.push_back(n_lazer);
        // Reset Time
        m_lastFireTime = GetTime();
        PlaySound(m_fireSound);
    }
}