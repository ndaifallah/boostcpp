#include "58_split_screen.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 58: Split-Screen & Multi-Viewport Rendering
// ============================================================

// CONCEPT: render the same scene from multiple viewpoints
// within a single window using render textures or scissor modes.
// - Split-screen for multiplayer games
// - Rear-view mirrors in racing games
// - Security camera feeds
// - Before/after effect comparison

void example_split_screen() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 58: Split-Screen Rendering");

    // Two cameras for split-screen
    Camera3D camLeft = {{0}};
    camLeft.position = {-8, 6, -8};
    camLeft.target = {0, 0, 0};
    camLeft.up = {0, 1, 0};
    camLeft.fovy = 60;
    camLeft.projection = CAMERA_PERSPECTIVE;

    Camera3D camRight = {{0}};
    camRight.position = {8, 6, 8};
    camRight.target = {0, 0, 0};
    camRight.up = {0, 1, 0};
    camRight.fovy = 60;
    camRight.projection = CAMERA_PERSPECTIVE;

    // Scene objects
    Vector3 cubePos = {-3, 1, 0};
    Vector3 spherePos = {3, 1, 0};
    float angle = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        angle += 30 * GetFrameTime();
        cubePos.z = sinf(angle * DEG2RAD) * 3;
        spherePos.x = 3 + cosf(angle * DEG2RAD * 0.7f) * 2;

        BeginDrawing();
        ClearBackground(DARKGRAY);

        // Left viewport
        BeginScissorMode(0, 0, screenWidth / 2, screenHeight);
        BeginMode3D(camLeft);
            DrawGrid(10, 2.0f);
            DrawCube(cubePos, 1.5f, 1.5f, 1.5f, RED);
            DrawCubeWires(cubePos, 1.5f, 1.5f, 1.5f, MAROON);
            DrawSphere(spherePos, 1.0f, BLUE);
            DrawSphereWires(spherePos, 1.0f, 16, 16, DARKBLUE);
            DrawPlane({0, 0, 0}, {10, 10}, GREEN);
        EndMode3D();
        EndScissorMode();

        // Right viewport
        BeginScissorMode(screenWidth / 2, 0, screenWidth / 2, screenHeight);
        BeginMode3D(camRight);
            DrawGrid(10, 2.0f);
            DrawCube(cubePos, 1.5f, 1.5f, 1.5f, RED);
            DrawCubeWires(cubePos, 1.5f, 1.5f, 1.5f, MAROON);
            DrawSphere(spherePos, 1.0f, BLUE);
            DrawSphereWires(spherePos, 1.0f, 16, 16, DARKBLUE);
            DrawPlane({0, 0, 0}, {10, 10}, GREEN);
        EndMode3D();
        EndScissorMode();

        // Separator line
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

        // Labels
        DrawText("PLAYER 1 (Left)", 20, 20, 20, RED);
        DrawText("PLAYER 2 (Right)", screenWidth / 2 + 20, 20, 20, BLUE);

        DrawText("Exercise 58: Split-Screen Rendering", 50, screenHeight - 30, 15, GRAY);
        DrawFPS(screenWidth - 100, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 58.1: Implement a 4-player split-screen (four quadrants).
// Each quadrant shows the scene from a different angle.
void challenge_quad_splitscreen() {
    std::cout << "Challenge 58.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   4 cameras at 90-degree intervals around a central object:
    //     - Front: (0, 3, 10)
    //     - Back: (0, 3, -10)
    //     - Left: (-10, 3, 0)
    //     - Right: (10, 3, 0)
    //   Draw each viewport in its quadrant
    //   Add colored borders and labels

    std::cout << "Hint: Use BeginScissorMode for each quadrant\n";
}

// CHALLENGE 58.2: Create a "rear-view mirror" effect by rendering
// a small camera view in the corner of the main screen.
void challenge_rearview_mirror() {
    std::cout << "Challenge 58.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Main view: third-person camera following an object
    //   Small viewport in top-right: camera behind the object
    //   Draw a border around the small viewport like a mirror frame
    //   Label it "REAR VIEW"

    std::cout << "Hint: Draw the mirror viewport last so it renders on top\n";
}

void exercise_split_screen() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 58: Split-Screen & Multi-Viewport\n";
    std::cout << "========================================\n";
    std::cout << "Opening split-screen demo - close window to continue...\n\n";

    example_split_screen();
    std::cout << "Split-screen demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_quad_splitscreen();
    challenge_rearview_mirror();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 58 complete!\n";
    std::cout << "========================================\n";
}
