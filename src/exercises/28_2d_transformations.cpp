#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 28: 2D Transformations
// ============================================================

// CONCEPT: 2D transformations in raylib
// - DrawRectanglePro(rect, origin, rotation, color): rotated rectangle
// - DrawTexturePro(texture, source, dest, origin, rotation, tint): full control
// - rlPushMatrix()/rlTranslatef()/rlRotatef()/rlPopMatrix(): manual transforms
// - Scaling: use DrawRectanglePro with scaled dest rect

void example_rotation() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 28: Rotation");

    SetTargetFPS(60);

    float angle = 0.0f;

    while (!WindowShouldClose()) {
        angle += GetFrameTime() * 50.0f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectanglePro(
                (Rectangle){400, 200, 150, 80},
                (Vector2){75, 40},
                angle,
                RED
            );

            DrawCircle(400, 200, 5, BLACK);

            DrawText("Rotating rectangle around its center", 250, 400, 20, DARKGRAY);
            DrawText(TextFormat("Angle: %.1f", angle), 50, 50, 20, DARKGRAY);
            DrawFPS(10, 80);

        EndDrawing();
    }

    CloseWindow();
}

void example_scale_and_origin() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 28: Scale & Origin");

    SetTargetFPS(60);

    float scale = 1.0f;
    bool growing = true;

    while (!WindowShouldClose()) {
        if (growing) {
            scale += GetFrameTime() * 0.5f;
            if (scale >= 3.0f) growing = false;
        } else {
            scale -= GetFrameTime() * 0.5f;
            if (scale <= 0.5f) growing = true;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectanglePro(
                (Rectangle){200, 225, 100, 100},
                (Vector2){0, 0},
                0,
                Fade(BLUE, 0.3f)
            );

            DrawRectanglePro(
                (Rectangle){200, 225, 100, 100},
                (Vector2){50, 50},
                0,
                Fade(RED, 0.3f)
            );

            DrawRectanglePro(
                (Rectangle){500, 225, 100, 100},
                (Vector2){50, 50},
                0,
                (Color){0, (unsigned char)(255 * (scale / 3.0f)), 255, 255}
            );

            float scaledW = 100 * scale;
            float scaledH = 100 * scale;
            DrawRectanglePro(
                (Rectangle){500, 225, 100, 100},
                (Vector2){50, 50},
                0,
                Fade(GREEN, 0.2f)
            );
            DrawRectangleLines(
                (int)(500 - scaledW/2), (int)(225 - scaledH/2),
                (int)scaledW, (int)scaledH, GREEN
            );

            DrawText("Origin: top-left", 180, 340, 15, DARKGRAY);
            DrawText("Origin: center", 480, 340, 15, DARKGRAY);

            DrawText("Pulse demo - scale changes over time", 250, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 28.1: Create a rotating windmill with 4 blades.
// - Draw a central circle (the hub)
// - Draw 4 rectangular blades at 90-degree offsets
// - Each blade rotates around the center
// - Use DrawRectanglePro with different rotations per blade
void challenge_windmill() {
    std::cout << "Challenge 28.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 600, "Windmill")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(SKYBLUE)
    //   float angle changes over time
    //   Draw 4 blades (rectangles) at angles: angle, angle+90, angle+180, angle+270
    //   Each blade uses DrawRectanglePro with center origin at (300, 300)
    //   Draw a circle in the center (hub)
    //   Draw a pole (rectangle from center to bottom)
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: blade rect = {300, 150, 20, 120} or similar, origin = {10, 120}?\n";
}

// CHALLENGE 28.2: Draw a solar system simulation with 3 planets orbiting a sun.
// Use DrawCircle for the sun, and DrawCircle or DrawCircleV for planets.
// Use sin/cos + orbital radius to compute planet positions.
void challenge_solar_system() {
    std::cout << "Challenge 28.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 600, "Solar System")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(BLACK)
    //   DrawCircle at center (400,300) radius 30, YELLOW for sun
    //   For 3 planets, maintain angles that increase each frame
    //   Planet positions: centerX + orbitRadius * cos(angle), centerY + orbitRadius * sin(angle)
    //   Different orbit radii and speeds for each planet
    //   Draw planets as circles
    //   Add orbit path lines (DrawCircleLines with low alpha)
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Use different speeds: angle1 += 0.02, angle2 += 0.015, angle3 += 0.01\n";
}

void exercise_2d_transformations() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 28: 2D Transformations\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_rotation();
    std::cout << "Example 1 done.\n";
    example_scale_and_origin();
    std::cout << "Example 2 done.\n";
    challenge_windmill();
    challenge_solar_system();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 28 complete!\n";
    std::cout << "========================================\n";
}
