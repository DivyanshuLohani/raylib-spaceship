#include "lazer.h"

Lazer::Lazer(Vector2 position, int speed)
{
    m_position = position;
    m_speed = speed;
    m_active = true;
}

Lazer::~Lazer()
{
}

void Lazer::Draw()
{
    DrawRectangle(m_position.x, m_position.y, 4, 15, YELLOW);
}

void Lazer::Update()
{
    if (m_active)
        m_position.y -= m_speed;
    else
        return;

    if (m_position.y < 0)
    {
        m_active = false;
    }
}
