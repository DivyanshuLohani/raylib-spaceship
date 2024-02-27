#include "game.h"
#include "enemy.h"

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

Game::Game()
{
    m_Font = LoadFontEx("Fonts/game.ttf", 64, 0, 0);
    m_explosionSound = LoadSound("Audio/explosion.wav");

    Init();
}

void Game::Init()
{
    m_alien_lazers.clear();
    m_aliens.clear();
    CreateAliens();
    m_lives = 3;
    m_run = true;
    m_alienDirection = 1;
    m_alienLazerFireTime = 0.0f;
    m_score = 0;
}

void Game::Draw()
{
    m_player.Draw();

    for (auto enemy : m_aliens)
    {
        enemy.Draw();
    }

    for (auto &lazer : m_player.m_lazers)
    {
        lazer.Draw();
    }

    for (auto &lazer : m_alien_lazers)
    {
        lazer.Draw();
    }

    DrawUI();
}

void Game::DrawUI()
{
    DrawRectangleRoundedLines(
        {
            10,
            10,
            (float)(GetScreenWidth() - 20),
            (float)(GetScreenHeight() - 20),
        },
        0.18f, 20, 2, YELLOW);
    DrawLineEx({10, 730}, {740, 730}, 3, YELLOW);

    if (m_run)
    {
        DrawTextEx(m_Font, "LEVEL 01", {570, 740}, 34, 2, YELLOW);
    }
    else
    {
        DrawTextEx(m_Font, "GAME OVER", {570, 740}, 34, 2, YELLOW);
        Vector2 f_size = MeasureTextEx(m_Font, "R to Restart", 64, 2);
        DrawTextEx(m_Font, "R to Restart", {
                                               ((int)GetScreenWidth() - f_size.x) / 2,
                                               ((int)GetScreenHeight() - f_size.y) / 2,
                                           },
                   34, 2, YELLOW);
    }

    // Spaceships
    float x = 50.0;
    for (int i = 0; i < m_lives; i++)
    {
        DrawTextureV(m_player.GetTexture(), {x, 745}, WHITE);
        x += 50;
    }

    // Score
    DrawTextEx(m_Font, "SCORE", {50, 15}, 34, 2, YELLOW);
    std::string scoreText = FormatWithLeadingZeros(m_score, 5);
    DrawTextEx(m_Font, scoreText.c_str(), {50, 40}, 34, 2, YELLOW);

    // DrawTextEx(m_Font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
    // std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
    // DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);
}

void Game::Update()
{
    UpdateLazers();

    if (!m_run)
    {
        if (IsKeyPressed(KEY_R))
        {
            Init();
        }
        return;
    }

    m_player.Update();
    MoveAliens();
    if (m_aliens.size() > 0)
    {
        ShootAlienLazers();
    }
    CheckCollision();
}

void Game::CreateAliens()
{
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 11; column++)
        {

            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            m_aliens.push_back(Enemy(static_cast<Enemytype>(alienType), {x, y}));
        }
    }
}

void Game::UpdateLazers()
{
    for (int i = 0; i < (int)m_player.m_lazers.size();)
    {
        if (m_player.m_lazers[i].m_active)
        {
            m_player.m_lazers[i].Update();
            i++;
        }
        else
        {
            m_player.m_lazers.erase(m_player.m_lazers.begin() + i);
        }
    }

    for (int i = 0; i < (int)m_alien_lazers.size();)
    {
        if (m_alien_lazers[i].m_active)
        {
            m_alien_lazers[i].Update();
            i++;
        }
        else
        {
            m_alien_lazers.erase(m_alien_lazers.begin() + i);
        }
    }
}

void Game::MoveAliens()
{
    for (auto &alien : m_aliens)
    {
        if (alien.m_position.x + alien.GetTexture().width + 25 > GetScreenWidth())
        {
            m_alienDirection = -1;
            MoveDownAliens(4);
        }
        if (alien.m_position.x < 25)
        {
            m_alienDirection = 1;
            MoveDownAliens(4);
        }
        alien.m_position.x += m_alienDirection;
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : m_aliens)
    {
        alien.m_position.y += distance;
    }
}

void Game::CheckCollision()
{

    Rectangle playerRect = {
        m_player.m_position.x,
        m_player.m_position.y,
        static_cast<float>(m_player.GetTexture().width),
        static_cast<float>(m_player.GetTexture().height)};

    Enemy alien;
    for (auto &lazer : m_player.m_lazers)
    {
        Rectangle lazerRect = {lazer.m_position.x,
                               lazer.m_position.y,
                               4,
                               15};
        if (CheckAlienCollision(lazerRect, alien))
        {
            lazer.m_active = false;
            PlaySound(m_explosionSound);
            switch (alien.GetType())
            {
            case ALIEN_1:
                m_score += 100;
                break;
            case ALIEN_2:
                m_score += 200;
                break;
            case ALIEN_3:
                m_score += 300;
                break;

            default:
                break;
            }
        }
    }

    if (CheckAlienCollision(playerRect, alien))
    {
        m_lives -= 1;
        if (m_lives <= 0)
        {
            m_run = false;
        }
    }

    for (auto &lazer : m_alien_lazers)
    {
        Rectangle lazerRect = {lazer.m_position.x,
                               lazer.m_position.y,
                               4,
                               15};
        if (CheckCollisionRecs(lazerRect, playerRect))
        {
            lazer.m_active = false;
            m_lives -= 1;
            if (m_lives <= 0)
            {
                m_run = false;
            }
            PlaySound(m_explosionSound);
        }
    }
}

bool Game::CheckAlienCollision(Rectangle rect, Enemy &o_alien)
{
    auto alien = m_aliens.begin();
    while (alien != m_aliens.end())
    {
        Rectangle alienRect = {alien->m_position.x,
                               alien->m_position.y,
                               static_cast<float>(alien->GetTexture().width),
                               static_cast<float>(alien->GetTexture().height)};

        if (CheckCollisionRecs(alienRect, rect))
        {
            alien = m_aliens.erase(alien);
            o_alien = Enemy(alien->GetType(), alien->m_position);
            return true;
        }
        else
        {
            ++alien;
        }
    }
    return false;
}

void Game::ShootAlienLazers()
{
    if (GetTime() - m_alienLazerFireTime <= 0.8f)
        return;

    m_alienLazerFireTime = GetTime();
    int alienIndex = GetRandomValue(0, m_aliens.size() > 0 ? (int)m_aliens.size() - 1 : 0);
    Enemy &alien = m_aliens[alienIndex];
    Lazer lazer({alien.m_position.x + alien.GetTexture().width / 2, alien.m_position.y}, -5);
    m_alien_lazers.push_back(lazer);
    PlaySound(m_player.m_fireSound);
}