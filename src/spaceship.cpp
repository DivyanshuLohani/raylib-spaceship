#include "spaceship.h"

Spaceship::Spaceship()
{
    m_texture = LoadTexture("Graphics/spaceship.png");
    m_position.x = (GetScreenWidth() - m_texture.width) / 2 ;
    m_position.y = (GetScreenHeight() - m_texture.height) - 20 ;
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
}
