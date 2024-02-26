#include "lazer.h"

Lazer::Lazer(Vector2 position, int speed)
{
    m_position = position;
    m_speed = speed;
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
    m_position.y -= m_speed;
}
