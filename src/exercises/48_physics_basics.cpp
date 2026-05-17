#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 48: Physics Basics
// ============================================================

// CONCEPT: simple physics simulation
// - Position: where the object is
// - Velocity: how fast it's moving (speed + direction)
// - Acceleration: how velocity changes over time
// - Gravity: constant downward acceleration
// - Friction: opposition to motion (reduces velocity)
// - Bounce: reflect velocity on collision with surfaces
// - Integration: position += velocity * dt, velocity += acceleration * dt

struct PhysicsBody {
    Vector2 pos;
    Vector2 vel;
    float radius;
    float mass;
    Color color;
};

void update_body(PhysicsBody& body, float dt, float gravity, float friction, int screenW, int screenH) {
    body.vel.y += gravity * dt;
    body.vel.x *= (1.0f - friction * dt);

    body.pos.x += body.vel.x * dt;
    body.pos.y += body.vel.y * dt;

    if (body.pos.x - body.radius < 0) {
        body.pos.x = body.radius;
        body.vel.x = -body.vel.x * 0.8f;
    }
    if (body.pos.x + body.radius > screenW) {
        body.pos.x = screenW - body.radius;
        body.vel.x = -body.vel.x * 0.8f;
    }
    if (body.pos.y + body.radius > screenH) {
        body.pos.y = screenH - body.radius;
        body.vel.y = -body.vel.y * 0.8f;
    }
    if (body.pos.y - body.radius < 0) {
        body.pos.y = body.radius;
        body.vel.y = -body.vel.y * 0.8f;
    }
}

void example_physics_simulation() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 48: Physics Basics");

    const int numBalls = 5;
    PhysicsBody balls[numBalls];

    for (int i = 0; i < numBalls; i++) {
        balls[i].pos = {(float)(200 + i * 100), (float)(50 + i * 30)};
        balls[i].vel = {(float)GetRandomValue(-100, 100), (float)GetRandomValue(-50, 50)};
        balls[i].radius = (float)(15 + i * 5);
        balls[i].mass = balls[i].radius;
        Color colors[] = {RED, BLUE, GREEN, ORANGE, PURPLE};
        balls[i].color = colors[i];
    }

    float gravity = 300.0f;
    float friction = 0.5f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (IsKeyDown(KEY_ONE)) gravity = 100;
        else if (IsKeyDown(KEY_TWO)) gravity = 300;
        else if (IsKeyDown(KEY_THREE)) gravity = 600;
        if (IsKeyDown(KEY_R)) {
            for (int i = 0; i < numBalls; i++) {
                balls[i].pos = {(float)(200 + i * 100), 50};
                balls[i].vel = {(float)GetRandomValue(-100, 100), 0};
            }
        }

        for (int i = 0; i < numBalls; i++) {
            update_body(balls[i], dt, gravity, friction, screenWidth, screenHeight);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < numBalls; i++) {
                DrawCircleV(balls[i].pos, balls[i].radius, balls[i].color);
                DrawCircleLines((int)balls[i].pos.x, (int)balls[i].pos.y, balls[i].radius, DARKGRAY);
            }

            DrawText("Physics Simulation", 50, 10, 25, DARKGRAY);
            DrawText("1: Low gravity  2: Normal gravity  3: High gravity", 50, 400, 18, DARKGRAY);
            DrawText("R: Reset", 700, 400, 18, DARKGRAY);
            DrawText(TextFormat("Gravity: %.0f", gravity), 50, 50, 18, DARKGRAY);
            DrawFPS(10, 80);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 48.1: Simulate projectile motion. When mouse is clicked,
// launch a ball from the bottom-center toward the mouse direction.
// Draw the trajectory as a dotted line.
void challenge_projectile() {
    std::cout << "Challenge 48.1 incomplete - fill in the TODOs!\n";

    // TODO: On click, create ball at bottom-center
    // Direction = normalize(mouse - start) * speed
    // gravity pulls it down
    // Draw trail of previous positions
    // Bonus: Predict and draw the parabolic arc before launching

    std::cout << "Hint: Vector2 dir = Vector2Normalize({mouse.x - startX, mouse.y - startY})\n";
}

// CHALLENGE 48.2: Implement a simple pendulum simulation.
// A bob attached to a fixed point swings under gravity.
// Use: angular_acceleration = -(g/L) * sin(angle)
//      angular_velocity += accel * dt
//      angle += angular_velocity * dt
void challenge_pendulum() {
    std::cout << "Challenge 48.2 incomplete - fill in the TODOs!\n";

    // TODO: Pendulum: fixed point + bob connected by a line
    // float angle = PI/4 (initial), float angularVel = 0
    // Each frame:
    //   float accel = -(9.8 / length) * sin(angle)
    //   angularVel += accel * dt
    //   angle += angularVel * dt
    //   angularVel *= 0.999 (damping)
    // Draw line from pivot to bob, bob as circle

    std::cout << "Hint: bobPos = {pivotX + L*sin(angle), pivotY + L*cos(angle)}\n";
}

void exercise_physics_basics() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 48: Physics Basics\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_physics_simulation();
    std::cout << "Example done.\n";
    challenge_projectile();
    challenge_pendulum();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 48 complete!\n";
    std::cout << "========================================\n";
}
