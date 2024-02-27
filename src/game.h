#pragma once
#include <raylib.h>
#include "spaceship.h"
#include "enemy.h"

class Game
{
public:
    Game();
    void Draw();
    void Update();

private:
    Spaceship m_player;
    std::vector<Enemy> m_aliens;
    std::vector<Lazer> m_alien_lazers;
    int m_lives;
    int m_score = 0;
    bool m_run = true;
    int m_alienDirection = 1;

    Font m_Font;
    Sound m_explosionSound;

    double m_alienLazerFireTime = 0.0f;

    void CreateAliens();

    void UpdateLazers();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void DrawUI();

    void ShootAlienLazers();

    // Load level
    void LoadLevel(int level);

    void CheckCollision();
    bool CheckAlienCollision(Rectangle rect, Enemy &alien);
};