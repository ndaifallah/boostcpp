#include "64_final_project.h"
#include <entt/entt.hpp>
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

// ============================================================
// EXERCISE 64: Final Project — Advanced ECS Tower Defense
// ============================================================

// CONCEPT: combine everything into a complete game
// - EnTT ECS for entity management
// - raylib for rendering and input
// - Multiple systems (movement, combat, spawning, rendering)
// - UI overlay, game states, particle effects
// - Save/load high score

// Components
struct Position { float x, y; };
struct Velocity { float vx, vy; float speed; };
struct Health { int current; int max; };
struct Damage { int amount; };
struct Radius { float r; };

struct PlayerTag {};
struct EnemyTag {};
struct ProjectileTag {};
struct TowerTag {};

struct Tower {
    enum Type { BASIC, SNIPER, SPLASH } type;
    float range;
    float fireRate;
    float cooldown;
    int cost;
};

struct Enemy {
    int reward;
    float speed;
};

struct Projectile {
    float speed;
    int damage;
};

struct Lifetime { float remaining; };

struct Particle {
    Vector2 vel;
    Color color;
    float life;
    float maxLife;
    float size;
};

struct ScoreDisplay {
    int score;
};

// Helper
float dist(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrtf(dx * dx + dy * dy);
}

void example_tower_defense() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 64: Final Project — ECS Tower Defense");

    entt::registry registry;

    // Game state
    int score = 0;
    int gold = 200;
    int lives = 20;
    int wave = 0;
    int enemiesPerWave = 5;
    int enemiesSpawned = 0;
    float spawnTimer = 0;
    float spawnInterval = 1.0f;
    bool waveActive = false;
    bool gameOver = false;
    bool placingTower = false;
    Tower::Type selectedTowerType = Tower::BASIC;

    // Path for enemies (waypoints)
    std::vector<Vector2> path = {
        {0, 300}, {150, 300}, {150, 100}, {350, 100},
        {350, 400}, {550, 400}, {550, 200}, {750, 200}
    };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();

        if (!gameOver) {
            // --- Spawning ---
            if (!waveActive) {
                wave++;
                enemiesPerWave = 5 + wave * 2;
                enemiesSpawned = 0;
                spawnInterval = fmaxf(0.3f, 1.0f - wave * 0.05f);
                waveActive = true;
            }

            spawnTimer += dt;
            if (waveActive && enemiesSpawned < enemiesPerWave && spawnTimer >= spawnInterval) {
                spawnTimer = 0;
                entt::entity e = registry.create();
                registry.emplace<Position>(e, path[0].x, path[0].y);
                registry.emplace<Velocity>(e, 0, 0, 60.0f + wave * 3.0f);
                registry.emplace<Health>(e, 20 + wave * 5, 20 + wave * 5);
                registry.emplace<Enemy>(e, 10 + wave * 2, 60.0f + wave * 3.0f);
                registry.emplace<Radius>(e, 12.0f);
                registry.emplace<EnemyTag>(e);
                enemiesSpawned++;
            }

            // Check if wave is done
            if (enemiesSpawned >= enemiesPerWave) {
                auto view = registry.view<EnemyTag>();
                if (view.size() == 0) {
                    waveActive = false;
                    gold += 20 + wave * 5; // Wave completion bonus
                }
            }

            // --- Tower Placement ---
            if (placingTower && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                // Check if not on path (simplified: not too close to path waypoints)
                bool onPath = false;
                for (auto &wp : path) {
                    if (dist(mouse.x, mouse.y, wp.x, wp.y) < 40) { onPath = true; break; }
                }
                if (!onPath && gold >= 50) {
                    entt::entity t = registry.create();
                    registry.emplace<Position>(t, mouse.x, mouse.y);
                    registry.emplace<Radius>(t, 15.0f);
                    registry.emplace<TowerTag>(t);

                    Tower tower;
                    tower.type = selectedTowerType;
                    tower.fireRate = (selectedTowerType == Tower::SNIPER) ? 0.5f :
                                     (selectedTowerType == Tower::SPLASH) ? 1.2f : 0.8f;
                    tower.range = (selectedTowerType == Tower::SNIPER) ? 300.0f :
                                  (selectedTowerType == Tower::SPLASH) ? 120.0f : 200.0f;
                    tower.cooldown = 0;
                    tower.cost = (selectedTowerType == Tower::SNIPER) ? 100 :
                                 (selectedTowerType == Tower::SPLASH) ? 150 : 50;
                    registry.emplace<Tower>(t, tower);

                    gold -= tower.cost;
                }
                placingTower = false;
            }

            // --- Tower Targeting & Shooting ---
            auto towerView = registry.view<Position, Tower, TowerTag>();
            auto enemyView = registry.view<Position, Health, EnemyTag>();

            for (auto entity : towerView) {
                auto &pos = towerView.get<Position>(entity);
                auto &twr = towerView.get<Tower>(entity);
                twr.cooldown -= dt;

                // Find closest enemy in range
                entt::entity target = entt::null;
                float closestDist = twr.range;
                for (auto e : enemyView) {
                    auto &ePos = enemyView.get<Position>(e);
                    float d = dist(pos.x, pos.y, ePos.x, ePos.y);
                    if (d < closestDist) {
                        closestDist = d;
                        target = e;
                    }
                }

                if (target != entt::null && twr.cooldown <= 0) {
                    twr.cooldown = twr.fireRate;
                    auto &targetPos = enemyView.get<Position>(target);

                    // Create projectile
                    entt::entity proj = registry.create();
                    registry.emplace<Position>(proj, pos.x, pos.y);
                    float dx = targetPos.x - pos.x;
                    float dy = targetPos.y - pos.y;
                    float d = sqrtf(dx * dx + dy * dy);
                    registry.emplace<Velocity>(proj, dx / d, dy / d, 300.0f);
                    registry.emplace<Projectile>(proj, 300.0f,
                        (twr.type == Tower::SNIPER) ? 40 : (twr.type == Tower::SPLASH) ? 15 : 25);
                    if (twr.type == Tower::SPLASH) {
                        registry.emplace<Radius>(proj, 30.0f);
                    }
                    registry.emplace<Lifetime>(proj, 2.0f);
                    registry.emplace<ProjectileTag>(proj);
                }
            }

            // --- Projectile Movement ---
            auto projView = registry.view<Position, Velocity, ProjectileTag>();
            for (auto entity : projView) {
                auto &pos = projView.get<Position>(entity);
                auto &vel = projView.get<Velocity>(entity);
                pos.x += vel.vx * vel.speed * dt;
                pos.y += vel.vy * vel.speed * dt;
            }

            // --- Enemy Movement ---
            auto moveView = registry.view<Position, Enemy, EnemyTag>();
            for (auto entity : moveView) {
                auto &pos = moveView.get<Position>(entity);
                auto &enemy = moveView.get<Enemy>(entity);

                // Find next waypoint
                int nextWp = -1;
                float closestDist = 999999;
                for (size_t i = 0; i < path.size(); i++) {
                    float d = dist(pos.x, pos.y, path[i].x, path[i].y);
                    if (d < closestDist && d > 5) {
                        // Prefer forward waypoints
                        if (i == 0 || dist(pos.x, pos.y, path[i-1].x, path[i-1].y) <
                                      dist(pos.x, pos.y, path[i].x, path[i].y) + 10) {
                            closestDist = d;
                            nextWp = (int)i;
                        }
                    }
                }

                if (nextWp >= 0) {
                    float dx = path[nextWp].x - pos.x;
                    float dy = path[nextWp].y - pos.y;
                    float d = sqrtf(dx * dx + dy * dy);
                    if (d > 2) {
                        pos.x += (dx / d) * enemy.speed * dt;
                        pos.y += (dy / d) * enemy.speed * dt;
                    }
                }

                // Reached end of path
                if (dist(pos.x, pos.y, path.back().x, path.back().y) < 20) {
                    lives--;
                    registry.destroy(entity);
                    if (lives <= 0) gameOver = true;
                }
            }

            // --- Projectile-Enemy Collision ---
            std::vector<entt::entity> toDestroy;
            for (auto p : registry.view<Position, Projectile, ProjectileTag>()) {
                auto &pPos = registry.get<Position>(p);
                auto &projComp = registry.get<Projectile>(p);
                bool splash = registry.all_of<Radius>(p);

                for (auto e : registry.view<Position, Health, EnemyTag>()) {
                    auto &ePos = registry.get<Position>(e);
                    auto &eHealth = registry.get<Health>(e);
                    float d = dist(pPos.x, pPos.y, ePos.x, ePos.y);
                    float hitRadius = splash ? registry.get<Radius>(p).r : 10.0f;

                    if (d < hitRadius) {
                        if (splash) {
                            eHealth.current -= projComp.damage;
                        } else {
                            eHealth.current -= projComp.damage;
                        }

                        if (eHealth.current <= 0) {
                            score += registry.get<Enemy>(e).reward;
                            gold += registry.get<Enemy>(e).reward;

                            // Death particles
                            for (int i = 0; i < 8; i++) {
                                entt::entity particle = registry.create();
                                registry.emplace<Position>(particle, ePos.x, ePos.y);
                                float angle = (float)i / 8 * PI * 2;
                                registry.emplace<Particle>(particle,
                                    Vector2{cosf(angle) * 80, sinf(angle) * 80},
                                    ORANGE, 0.6f, 0.6f, 4.0f);
                            }

                            registry.destroy(e);
                        }

                        if (!splash) {
                            toDestroy.push_back(p);
                            break;
                        }
                    }
                }
            }

            for (auto e : toDestroy) {
                if (registry.valid(e)) registry.destroy(e);
            }

            // --- Lifetime & cleanup ---
            for (auto entity : registry.view<Lifetime>()) {
                auto &life = registry.get<Lifetime>(entity);
                life.remaining -= dt;
                if (life.remaining <= 0) registry.destroy(entity);
            }

            // --- Particle Update ---
            for (auto entity : registry.view<Particle, Position>()) {
                auto &p = registry.get<Particle>(entity);
                auto &pos = registry.get<Position>(entity);
                pos.x += p.vel.x * dt;
                pos.y += p.vel.y * dt;
                p.vel.x *= 0.96f;
                p.vel.y *= 0.96f;
                p.life -= dt;
                if (p.life <= 0) registry.destroy(entity);
            }
        }

        // --- Drawing ---
        BeginDrawing();
        ClearBackground(BLACK);

        if (!gameOver) {
            // Draw path
            for (size_t i = 0; i < path.size() - 1; i++) {
                DrawLineV(path[i], path[i + 1], DARKGRAY);
                DrawCircleV(path[i], 4, GRAY);
            }
            DrawCircleV(path.back(), 6, RED); // Endpoint (base)

            // Draw towers
            for (auto entity : registry.view<Position, Tower, TowerTag>()) {
                auto &pos = registry.get<Position>(entity);
                auto &twr = registry.get<Tower>(entity);
                Color towerColor;
                switch (twr.type) {
                    case Tower::BASIC: towerColor = BLUE; break;
                    case Tower::SNIPER: towerColor = PURPLE; break;
                    case Tower::SPLASH: towerColor = RED; break;
                }
                DrawCircleV({pos.x, pos.y}, 15, towerColor);
                DrawCircleLines((int)pos.x, (int)pos.y, 15, WHITE);

                // Range indicator (when placing or selected)
                if (placingTower) {
                    DrawCircleLines((int)pos.x, (int)pos.y, (int)twr.range, Fade(towerColor, 0.3f));
                }
            }

            // Placeholder tower at mouse
            if (placingTower) {
                Color placeColor;
                switch (selectedTowerType) {
                    case Tower::BASIC: placeColor = BLUE; break;
                    case Tower::SNIPER: placeColor = PURPLE; break;
                    case Tower::SPLASH: placeColor = RED; break;
                }
                DrawCircleV(mouse, 15, Fade(placeColor, 0.5f));
                DrawCircleLines((int)mouse.x, (int)mouse.y, 15, Fade(WHITE, 0.5f));

                // Range
                float range = (selectedTowerType == Tower::SNIPER) ? 300 :
                              (selectedTowerType == Tower::SPLASH) ? 120 : 200;
                DrawCircleLines((int)mouse.x, (int)mouse.y, (int)range, Fade(placeColor, 0.2f));
            }

            // Draw enemies
            for (auto entity : registry.view<Position, Health, EnemyTag>()) {
                auto &pos = registry.get<Position>(entity);
                auto &hp = registry.get<Health>(entity);
                DrawCircleV({pos.x, pos.y}, 12, RED);
                DrawCircleLines((int)pos.x, (int)pos.y, 12, MAROON);
                // Health bar
                float hpPct = (float)hp.current / hp.max;
                DrawRectangle((int)pos.x - 15, (int)pos.y - 20, 30, 4, DARKGRAY);
                DrawRectangle((int)pos.x - 15, (int)pos.y - 20, (int)(30 * hpPct), 4, GREEN);
            }

            // Draw projectiles
            for (auto entity : registry.view<Position, ProjectileTag>()) {
                auto &pos = registry.get<Position>(entity);
                Color pColor = registry.all_of<Radius>(entity) ? RED : YELLOW;
                DrawCircleV({pos.x, pos.y}, 4, pColor);
            }

            // Draw particles
            for (auto entity : registry.view<Particle, Position>()) {
                auto &p = registry.get<Particle>(entity);
                auto &pos = registry.get<Position>(entity);
                float alpha = p.life / p.maxLife;
                DrawCircleV({pos.x, pos.y}, p.size * alpha, Fade(p.color, alpha));
            }

            // UI
            DrawText(TextFormat("Score: %d", score), 50, 20, 25, WHITE);
            DrawText(TextFormat("Gold: %d", gold), 50, 48, 20, YELLOW);
            DrawText(TextFormat("Lives: %d", lives), 50, 72, 20, RED);
            DrawText(TextFormat("Wave: %d", wave), 50, 96, 18, LIGHTGRAY);

            if (placingTower) {
                DrawText("Click to place tower", 300, 20, 20, GREEN);
            }

            DrawText("1: Basic (50g)  2: Sniper (100g)  3: Splash (150g)", 50, 560, 14, GRAY);
            DrawText("B: Buy tower   SPACE: Start next wave", 50, 578, 14, GRAY);

            // Tower selection
            if (IsKeyPressed(KEY_ONE)) { selectedTowerType = Tower::BASIC; placingTower = true; }
            if (IsKeyPressed(KEY_TWO)) { selectedTowerType = Tower::SNIPER; placingTower = true; }
            if (IsKeyPressed(KEY_THREE)) { selectedTowerType = Tower::SPLASH; placingTower = true; }
            if (IsKeyPressed(KEY_B)) { placingTower = !placingTower; }
            if (IsKeyPressed(KEY_SPACE) && !waveActive) { waveActive = true; }

            // Cancel placement
            if (placingTower && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                placingTower = false;
            }
        } else {
            DrawText("GAME OVER", 280, 200, 50, RED);
            DrawText(TextFormat("Final Score: %d", score), 310, 280, 30, WHITE);
            DrawText(TextFormat("Waves Survived: %d", wave), 310, 320, 20, LIGHTGRAY);
            DrawText("Press R to restart", 320, 380, 20, GRAY);

            if (IsKeyPressed(KEY_R)) {
                registry.clear();
                score = 0;
                gold = 200;
                lives = 20;
                wave = 0;
                enemiesSpawned = 0;
                spawnTimer = 0;
                waveActive = false;
                gameOver = false;
            }
        }

        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 64.1: Add enemy type variety with different components.
// Implement a fast runner, a tank (high HP, slow), and a boss enemy.
void challenge_enemy_types() {
    std::cout << "Challenge 64.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   enum class EnemyType { RUNNER, TANK, BOSS, NORMAL };
    //   struct EnemyTypeComponent { EnemyType type; };
    //   Runner: high speed, low HP
    //   Tank: low speed, very high HP, rewards more gold
    //   Boss: spawns every 5 waves, huge HP, rewards lots
    //   Use registry.view<EnemyTypeComponent, ...>() to differentiate

    std::cout << "Hint: Check wave number to determine enemy types to spawn\n";
}

// CHALLENGE 64.2: Implement a slow/freeze tower that reduces enemy speed.
// Add a SlowEffect component to enemies and a SlowTower tower type.
void challenge_slow_tower() {
    std::cout << "Challenge 64.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct SlowEffect { float factor; float duration; };
    //   Create SlowTower type (KEY_4 to select, 80g cost)
    //   On hit: emplace<SlowEffect>(enemy, 0.5f, 3.0f)
    //   In enemy movement: if has SlowEffect, multiply speed by factor
    //   Decrease duration each frame, remove when expired

    std::cout << "Hint: Check SlowEffect in enemy movement, apply speed multiplier\n";
}

// CHALLENGE 64.3: Add sound effects for tower shooting, enemy death,
// wave start, and game over. Use raylib's audio functions.
void challenge_sound_fx() {
    std::cout << "Challenge 64.3 incomplete - fill in the TODOs!\n";

    // TODO:
    //   InitAudioDevice()
    //   Generate wave with GenWaveSquare/GenWaveSawtooth or load from file
    //   Play sounds on events:
    //     - Tower fires: short beep
    //     - Enemy dies: short noise
    //     - Wave starts: ascending tone
    //     - Game over: descending tone
    //   CloseAudioDevice() before CloseWindow()

    std::cout << "Hint: Use LoadSoundFromWave(GenWaveSquare(...)) for procedural sounds\n";
}

void exercise_final_project() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 64: Final Project\n";
    std::cout << "========================================\n";
    std::cout << "ECS Tower Defense - close window to continue...\n\n";

    example_tower_defense();
    std::cout << "Final project closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_enemy_types();
    challenge_slow_tower();
    challenge_sound_fx();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 64 complete!\n";
    std::cout << "========================================\n";
}
