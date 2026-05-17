#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// ============================================================
// EXERCISE 49: Mini Game
// ============================================================

// CONCEPT: combining everything into a complete game
// - Player movement (keyboard)
// - Collision detection
// - Game state management
// - Score tracking
// - Particle effects
// - Sound effects (optional)
// - UI overlay (score, lives, game over)

// A simple space shooter: player moves + shoots at falling enemies

struct Bullet {
    Vector2 pos;
    float speed;
    bool active;
};

struct Enemy {
    Vector2 pos;
    float radius;
    float speed;
    bool active;
    Color color;
};

void example_space_shooter() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 49: Space Shooter");

    Vector2 player = {400, 500};
    float playerRadius = 20;
    float playerSpeed = 300.0f;

    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;

    int score = 0;
    int lives = 3;
    float spawnTimer = 0;
    float spawnInterval = 1.5f;
    bool gameOver = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (!gameOver) {
            // Update player
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= playerSpeed * dt;
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += playerSpeed * dt;
            player.x = Clamp(player.x, playerRadius, screenWidth - playerRadius);

            // Shoot
            if (IsKeyPressed(KEY_SPACE)) {
                bullets.push_back({{player.x, player.y - playerRadius}, 500, true});
            }

            // Update bullets
            for (auto& b : bullets) {
                if (b.active) {
                    b.pos.y -= b.speed * dt;
                    if (b.pos.y < -10) b.active = false;
                }
            }

            // Spawn enemies
            spawnTimer += dt;
            if (spawnTimer >= spawnInterval) {
                spawnTimer = 0;
                Enemy e;
                e.pos = {(float)GetRandomValue(30, screenWidth - 30), -20};
                e.radius = (float)GetRandomValue(15, 25);
                e.speed = (float)GetRandomValue(50, 150);
                e.active = true;
                Color colors[] = {RED, MAROON, PURPLE, ORANGE};
                e.color = colors[GetRandomValue(0, 3)];
                enemies.push_back(e);
                spawnInterval = Clamp(spawnInterval - 0.02f, 0.5f, 1.5f);
            }

            // Update enemies
            for (auto& e : enemies) {
                if (e.active) {
                    e.pos.y += e.speed * dt;
                    if (e.pos.y > screenHeight + e.radius) e.active = false;
                }
            }

            // Bullet-Enemy collision
            for (auto& b : bullets) {
                if (!b.active) continue;
                for (auto& e : enemies) {
                    if (!e.active) continue;
                    float dx = b.pos.x - e.pos.x;
                    float dy = b.pos.y - e.pos.y;
                    if (dx * dx + dy * dy < e.radius * e.radius) {
                        b.active = false;
                        e.active = false;
                        score += 10;
                    }
                }
            }

            // Player-Enemy collision
            for (auto& e : enemies) {
                if (!e.active) continue;
                float dx = player.x - e.pos.x;
                float dy = player.y - e.pos.y;
                if (dx * dx + dy * dy < (playerRadius + e.radius) * (playerRadius + e.radius)) {
                    e.active = false;
                    lives--;
                    if (lives <= 0) gameOver = true;
                }
            }

            // Cleanup
            bullets.erase(
                std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return !b.active; }),
                bullets.end());
            enemies.erase(
                std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return !e.active; }),
                enemies.end());
        } else {
            if (IsKeyPressed(KEY_R)) {
                gameOver = false;
                score = 0;
                lives = 3;
                spawnInterval = 1.5f;
                spawnTimer = 0;
                bullets.clear();
                enemies.clear();
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);

            if (!gameOver) {
                // Draw stars (background)
                for (int i = 0; i < 50; i++) {
                    DrawCircle(
                        (i * 137 + 50) % screenWidth,
                        (int)((i * 97 + (int)(GetTime() * 20)) % screenHeight),
                        1, WHITE);
                }

                // Player
                DrawCircleV(player, playerRadius, GREEN);
                DrawCircleLines((int)player.x, (int)player.y, playerRadius, DARKGREEN);
                Vector2 tip = {player.x, player.y - playerRadius - 10};
                Vector2 left = {player.x - 10, player.y + 5};
                Vector2 right = {player.x + 10, player.y + 5};
                DrawTriangle(tip, left, right, DARKGREEN);

                // Bullets
                for (const auto& b : bullets) {
                    if (b.active) DrawCircle((int)b.pos.x, (int)b.pos.y, 3, YELLOW);
                }

                // Enemies
                for (const auto& e : enemies) {
                    if (e.active) {
                        DrawCircleV(e.pos, e.radius, e.color);
                        DrawCircleLines((int)e.pos.x, (int)e.pos.y, e.radius, DARKGRAY);
                    }
                }

                // UI
                DrawText(TextFormat("Score: %d", score), 50, 20, 25, WHITE);
                DrawText(TextFormat("Lives: %d", lives), 50, 50, 25, WHITE);
                DrawText(TextFormat("Level: %.1f", 1.0f / spawnInterval), 650, 20, 20, WHITE);
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

// CHALLENGE 49.1: Add enemy explosion particles when enemies are destroyed.
// Spawn 10-20 particles at the enemy's position that scatter outward.
void challenge_add_explosions() {
    std::cout << "Challenge 49.1 incomplete - fill in the TODOs!\n";

    // TODO: When an enemy is destroyed by a bullet:
    //   Create 10-15 particles at enemy position
    //   Each has random velocity (direction * speed)
    //   Fade out over 0.5 seconds
    //   Draw as small colored circles

    std::cout << "Hint: Use a Particle struct with pos, vel, life, color\n";
}

// CHALLENGE 49.2: Add different enemy types with different behaviors.
// - Basic: falls straight down
// - Zigzag: moves left-right while falling
// - Fast: moves quickly but smaller
void challenge_enemy_variety() {
    std::cout << "Challenge 49.2 incomplete - fill in the TODOs!\n";

    // TODO: EnemyType enum { BASIC, ZIGZAG, FAST }
    // Zigzag: e.pos.x += sin(time * frequency) * amplitude
    // Fast: speed higher, radius smaller
    // Different colors per type
    // Different score values per type

    std::cout << "Hint: Add a type field to Enemy struct, switch on update\n";
}

// CHALLENGE 49.3: Add power-ups that occasionally spawn and give the player
// temporary benefits (rapid fire, shield, extra life).
void challenge_powerups() {
    std::cout << "Challenge 49.3 incomplete - fill in the TODOs!\n";

    // TODO: PowerUp struct with type (RAPID_FIRE, SHIELD, EXTRA_LIFE)
    // Random spawn, falls like enemies
    // On collision with player: activate effect
    // Rapid fire: shoot faster (reduce cooldown for N seconds)
    // Shield: absorb one hit
    // Extra life: lives++

    std::cout << "Hint: Add a float powerUpTimer to track active power-up duration\n";
}

void exercise_mini_game() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 49: Mini Game (Space Shooter)\n";
    std::cout << "========================================\n";
    std::cout << "Opening the mini game - close window to continue...\n\n";

    example_space_shooter();
    std::cout << "Mini game closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_add_explosions();
    challenge_enemy_variety();
    challenge_powerups();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 49 complete!\n";
    std::cout << "========================================\n";
}
