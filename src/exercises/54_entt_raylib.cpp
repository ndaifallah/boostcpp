#include "54_entt_raylib.h"
#include <entt/entt.hpp>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// ============================================================
// EXERCISE 54: EnTT + raylib Integration (ECS Space Shooter)
// ============================================================

// CONCEPT: Use an EnTT registry to manage game entities,
// with raylib handling rendering, input, and audio.

// Components
struct Transform2D {
    Vector2 pos;
    Vector2 scale;
    float rot;
};

struct Velocity {
    Vector2 dir;
    float speed;
};

struct Health {
    int current;
    int max;
};

struct Sprite {
    Color color;
    float radius;
};

struct PlayerTag {};
struct EnemyTag {};
struct BulletTag {};

struct Lifetime {
    float remaining;
};

void example_ecs_space_shooter() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 54: EnTT + raylib ECS Space Shooter");

    entt::registry registry;

    // Player
    entt::entity player = registry.create();
    registry.emplace<Transform2D>(player, Vector2{400, 500}, Vector2{1, 1}, 0);
    registry.emplace<Velocity>(player, Vector2{0, 0}, 300.0f);
    registry.emplace<Health>(player, 3, 3);
    registry.emplace<Sprite>(player, GREEN, 20.0f);
    registry.emplace<PlayerTag>(player);

    int score = 0;
    float spawnTimer = 0;
    float spawnInterval = 1.2f;
    bool gameOver = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            // Player input
            auto &pTrans = registry.get<Transform2D>(player);
            auto &pVel = registry.get<Velocity>(player);
            pVel.dir = {0, 0};
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) pVel.dir.x -= 1;
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) pVel.dir.x += 1;
            if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) pVel.dir.y -= 1;
            if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) pVel.dir.y += 1;

            // Normalize diagonal movement
            float len = sqrtf(pVel.dir.x * pVel.dir.x + pVel.dir.y * pVel.dir.y);
            if (len > 0) {
                pVel.dir.x /= len;
                pVel.dir.y /= len;
            }

            pTrans.pos.x += pVel.dir.x * pVel.speed * dt;
            pTrans.pos.y += pVel.dir.y * pVel.speed * dt;
            pTrans.pos.x = Clamp(pTrans.pos.x, 20, screenWidth - 20);
            pTrans.pos.y = Clamp(pTrans.pos.y, 20, screenHeight - 20);

            // Shoot
            static float shootCooldown = 0;
            shootCooldown -= dt;
            if (IsKeyDown(KEY_SPACE) && shootCooldown <= 0) {
                shootCooldown = 0.2f;
                entt::entity b = registry.create();
                registry.emplace<Transform2D>(b, Vector2{pTrans.pos.x, pTrans.pos.y - 25}, Vector2{1, 1}, 0);
                registry.emplace<Velocity>(b, Vector2{0, -1}, 600.0f);
                registry.emplace<Sprite>(b, YELLOW, 4.0f);
                registry.emplace<Lifetime>(b, 2.0f);
                registry.emplace<BulletTag>(b);
            }

            // Spawn enemies
            spawnTimer += dt;
            if (spawnTimer >= spawnInterval) {
                spawnTimer = 0;
                entt::entity e = registry.create();
                registry.emplace<Transform2D>(e,
                    Vector2{(float)GetRandomValue(30, screenWidth - 30), -20},
                    Vector2{1, 1}, 0);
                registry.emplace<Velocity>(e,
                    Vector2{(float)GetRandomValue(-30, 30), (float)GetRandomValue(60, 150)},
                    1.0f);
                registry.emplace<Health>(e, 1, 1);
                Color colors[] = {RED, MAROON, PURPLE, ORANGE};
                registry.emplace<Sprite>(e, colors[GetRandomValue(0, 3)], (float)GetRandomValue(15, 25));
                registry.emplace<EnemyTag>(e);
                spawnInterval = Clamp(spawnInterval - 0.015f, 0.4f, 1.2f);
            }

            // Movement system
            auto moveView = registry.view<Transform2D, Velocity>();
            for (auto entity : moveView) {
                auto &t = moveView.get<Transform2D>(entity);
                auto &v = moveView.get<Velocity>(entity);
                t.pos.x += v.dir.x * v.speed * dt;
                t.pos.y += v.dir.y * v.speed * dt;
            }

            // Lifetime system
            auto lifeView = registry.view<Lifetime>();
            for (auto entity : lifeView) {
                auto &life = lifeView.get<Lifetime>(entity);
                life.remaining -= dt;
                if (life.remaining <= 0) {
                    registry.destroy(entity);
                }
            }

            // Remove out-of-bounds enemies
            auto enemyView = registry.view<Transform2D, EnemyTag>();
            for (auto entity : enemyView) {
                auto &t = enemyView.get<Transform2D>(entity);
                if (t.pos.y > screenHeight + 50 || t.pos.x < -50 || t.pos.x > screenWidth + 50) {
                    registry.destroy(entity);
                }
            }

            // Bullet-Enemy collision
            auto bulletView = registry.view<Transform2D, BulletTag>();
            auto enemyView2 = registry.view<Transform2D, EnemyTag>();
            std::vector<entt::entity> toDestroy;

            for (auto bullet : bulletView) {
                auto &bPos = bulletView.get<Transform2D>(bullet).pos;
                for (auto enemy : enemyView2) {
                    auto &ePos = enemyView2.get<Transform2D>(enemy).pos;
                    auto &eSprite = registry.get<Sprite>(enemy);
                    float dx = bPos.x - ePos.x;
                    float dy = bPos.y - ePos.y;
                    if (dx * dx + dy * dy < eSprite.radius * eSprite.radius) {
                        toDestroy.push_back(bullet);
                        toDestroy.push_back(enemy);
                        score += 10;
                    }
                }
            }

            for (auto e : toDestroy) {
                if (registry.valid(e)) registry.destroy(e);
            }

            // Enemy-Player collision
            auto &pSprite = registry.get<Sprite>(player);
            auto &pPos = registry.get<Transform2D>(player).pos;
            for (auto enemy : enemyView2) {
                auto &ePos = enemyView2.get<Transform2D>(enemy).pos;
                auto &eSprite = registry.get<Sprite>(enemy);
                float dx = pPos.x - ePos.x;
                float dy = pPos.y - ePos.y;
                if (dx * dx + dy * dy < (pSprite.radius + eSprite.radius) * (pSprite.radius + eSprite.radius)) {
                    registry.destroy(enemy);
                    auto &h = registry.get<Health>(player);
                    h.current--;
                    if (h.current <= 0) {
                        gameOver = true;
                    }
                }
            }

            // Check if player is still alive
            if (!registry.valid(player)) gameOver = true;
        } else {
            if (IsKeyPressed(KEY_R)) {
                // Reset game
                registry.clear();
                player = registry.create();
                registry.emplace<Transform2D>(player, Vector2{400, 500}, Vector2{1, 1}, 0);
                registry.emplace<Velocity>(player, Vector2{0, 0}, 300.0f);
                registry.emplace<Health>(player, 3, 3);
                registry.emplace<Sprite>(player, GREEN, 20.0f);
                registry.emplace<PlayerTag>(player);
                score = 0;
                spawnTimer = 0;
                spawnInterval = 1.2f;
                gameOver = false;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        if (!gameOver) {
            // Stars background
            for (int i = 0; i < 60; i++) {
                DrawCircle(
                    (i * 137 + 50) % screenWidth,
                    (int)((i * 97 + (int)(GetTime() * 30)) % screenHeight),
                    1, WHITE);
            }

            // Draw all entities with Sprite + Transform2D
            auto drawView = registry.view<Sprite, Transform2D>();
            for (auto entity : drawView) {
                auto &s = drawView.get<Sprite>(entity);
                auto &t = drawView.get<Transform2D>(entity);
                DrawCircleV(t.pos, s.radius, s.color);
                DrawCircleLines((int)t.pos.x, (int)t.pos.y, s.radius, DARKGRAY);
            }

            // Draw player ship shape
            if (registry.valid(player) && registry.all_of<Sprite>(player)) {
                auto &pTrans = registry.get<Transform2D>(player);
                auto &pSpr = registry.get<Sprite>(player);
                Vector2 tip = {pTrans.pos.x, pTrans.pos.y - pSpr.radius - 10};
                Vector2 left = {pTrans.pos.x - 12, pTrans.pos.y + 8};
                Vector2 right = {pTrans.pos.x + 12, pTrans.pos.y + 8};
                DrawTriangle(tip, left, right, DARKGREEN);
            }

            // UI
            if (registry.valid(player)) {
                auto &h = registry.get<Health>(player);
                DrawText(TextFormat("Health: %d/%d", h.current, h.max), 50, 20, 25, WHITE);
            }
            DrawText(TextFormat("Score: %d", score), 50, 50, 25, WHITE);
            DrawText(TextFormat("Wave: %.1f", 1.0f / spawnInterval), 650, 20, 20, WHITE);
            DrawText(TextFormat("Entities: %zu", registry.storage<entt::entity>().size()), 650, 45, 15, GRAY);
        } else {
            DrawText("GAME OVER", 250, 200, 50, RED);
            DrawText(TextFormat("Final Score: %d", score), 300, 280, 30, WHITE);
            DrawText("Press R to restart", 320, 350, 20, GRAY);
        }

        DrawFPS(700, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 54.1: Add power-ups that spawn occasionally.
// Create a PowerUp component with a type enum (SPEED_BOOST, SHIELD, EXTRA_LIFE).
void challenge_powerup_component() {
    std::cout << "Challenge 54.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   enum class PowerUpType { SPEED_BOOST, SHIELD, EXTRA_LIFE };
    //   struct PowerUp { PowerUpType type; };
    //   Spawn them occasionally (use a timer in the game loop)
    //   PowerUp entity has Sprite + Transform2D + PowerUp
    //   On Player-PowerUp collision: apply effect
    //   Speed boost: double player speed for 5 seconds
    //   Shield: absorb one hit
    //   Extra life: health.current++

    std::cout << "Hint: Add PowerUpTag too, and check collision in the main loop\n";
}

// CHALLENGE 54.2: Add enemy variety using components.
// Different enemy behaviors: straight, zigzag, chasing.
void challenge_enemy_behaviors() {
    std::cout << "Challenge 54.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   enum class EnemyBehavior { STRAIGHT, ZIGZAG, CHASER };
    //   struct Behavior { EnemyBehavior type; float timer; };
    //   In movement system: check if entity has Behavior
    //   STRAIGHT: move down
    //   ZIGZAG: dir.x oscillates with sin(time)
    //   CHASER: dir points toward player

    std::cout << "Hint: Use registry.view<Transform2D, Velocity, Behavior, EnemyTag>()\n";
}

// CHALLENGE 54.3: Add an explosion particle effect when enemies die.
// Use a Particle component with lifetime, velocity, and color.
void challenge_explosion_particles() {
    std::cout << "Challenge 54.3 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct Particle { Vector2 vel; Color startColor; Color endColor; float life; float maxLife; };
    //   When enemy is destroyed: spawn 10-20 particle entities
    //   Particle system: update position, interpolate color, destroy when life <= 0

    std::cout << "Hint: Draw particles with fading alpha and shrinking radius\n";
}

void exercise_entt_raylib() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 54: EnTT + raylib Integration\n";
    std::cout << "========================================\n";
    std::cout << "ECS Space Shooter - close window to continue...\n\n";

    example_ecs_space_shooter();
    std::cout << "Game closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_powerup_component();
    challenge_enemy_behaviors();
    challenge_explosion_particles();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 54 complete!\n";
    std::cout << "========================================\n";
}
