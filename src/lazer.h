#pragma once
#include <raylib.h>

class Lazer {
    public:
        Lazer(Vector2 position, int speed);
        ~Lazer();
        void Draw();
        void Update();
    
    private:
        Vector2 m_position;
        int m_speed;
};