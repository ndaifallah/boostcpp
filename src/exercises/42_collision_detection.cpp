#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>

// ============================================================
// EXERCISE 42: Collision Detection
// ============================================================

// CONCEPT: collision detection in raylib
// - CheckCollisionRecs(rect1, rect2): rectangle vs rectangle
// - CheckCollisionCircles(center1, radius1, center2, radius2): circle vs circle
// - CheckCollisionCircleRec(center, radius, rect): circle vs rectangle
// - CheckCollisionPointRec(point, rect): point vs rectangle
// - CheckCollisionPointCircle(point, center, radius): point vs circle
// - CheckCollisionPointTriangle(point, v1, v2, v3): point vs triangle
// - CheckCollisionLines(p1, p2, p3, p4, &contact): line vs line
// - GetCollisionRec(rect1, rect2): overlapping region

void example_collision_basics() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 42: Collision Basics");

    Rectangle player = {350, 200, 100, 100};
    Rectangle obstacles[] = {
        {100, 100, 80, 80},
        {600, 300, 100, 60},
        {200, 300, 60, 100},
        {600, 50, 60, 60}
    };
    int numObstacles = 4;

    Vector2 circleCenter = {400, 225};
    float circleRadius = 40;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) player.x += 5;
        if (IsKeyDown(KEY_LEFT)) player.x -= 5;
        if (IsKeyDown(KEY_DOWN)) player.y += 5;
        if (IsKeyDown(KEY_UP)) player.y -= 5;

        player.x = Clamp(player.x, 0, screenWidth - player.width);
        player.y = Clamp(player.y, 0, screenHeight - player.height);

        bool collides = false;
        for (int i = 0; i < numObstacles; i++) {
            if (CheckCollisionRecs(player, obstacles[i])) {
                collides = true;
                break;
            }
        }

        bool circleCollision = CheckCollisionRecs(player, (Rectangle){
            circleCenter.x - circleRadius, circleCenter.y - circleRadius,
            circleRadius * 2, circleRadius * 2
        });

        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw obstacles
            for (int i = 0; i < numObstacles; i++) {
                DrawRectangleRec(obstacles[i], DARKGRAY);
                DrawRectangleLinesEx(obstacles[i], 2, BLACK);
            }

            DrawCircleV(circleCenter, circleRadius, circleCollision ? ORANGE : BLUE);

            // Draw player
            DrawRectangleRec(player, collides ? RED : GREEN);
            DrawRectangleLinesEx(player, 2, collides ? MAROON : DARKGREEN);

            DrawText(TextFormat("Collision: %s", collides || circleCollision ? "YES" : "no"), 50, 10, 25, collides ? RED : DARKGRAY);
            DrawText("Use ARROW KEYS to move", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 50);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 42.1: Create a simple game where the player (circle) must
// avoid falling obstacles (rectangles). Track score and game over.
void challenge_avoid_obstacles() {
    std::cout << "Challenge 42.1 incomplete - fill in the TODOs!\n";

    // TODO: Player circle at bottom, controlled by LEFT/RIGHT
    // Obstacles fall from top (rectangles with random X position)
    // If CheckCollisionCircleRec(obstacle, player): game over
    // Score = time survived
    // Press R to restart

    std::cout << "Hint: Spawn obstacles at random X, move y += speed*dt each frame\n";
}

// CHALLENGE 42.2: Create a bouncing ball simulation with wall and paddle collision.
// Ball bounces off top/left/right walls, paddle at bottom reflects it.
// Lose when ball passes the paddle.
void challenge_bouncing_ball() {
    std::cout << "Challenge 42.2 incomplete - fill in the TODOs!\n";

    // TODO: Ball: position + velocity (dx, dy)
    // Paddle: rectangle controlled by mouse X
    // If ball hits paddle: dy = -dy (reverse)
    // If ball hits walls: dx = -dx or dy = -dy
    // If ball.y > screenHeight: game over

    std::cout << "Hint: Use CheckCollisionCircleRec(ball, paddle) for bounce\n";
}

void exercise_collision_detection() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 42: Collision Detection\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_collision_basics();
    std::cout << "Example done.\n";
    challenge_avoid_obstacles();
    challenge_bouncing_ball();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 42 complete!\n";
    std::cout << "========================================\n";
}
