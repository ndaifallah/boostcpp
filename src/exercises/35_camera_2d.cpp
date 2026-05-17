#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 35: Camera 2D
// ============================================================

// CONCEPT: 2D camera in raylib
// - Camera2D struct: offset, target, rotation, zoom
// - BeginMode2D(camera) / EndMode2D(): world-space drawing
// - Camera follows a target, smoothly pans with offset
// - Zoom > 1 = magnify, < 1 = shrink
// - Rotation rotates the view
// - GetScreenToWorld2D(mouse, camera): convert screen coords to world

void example_camera_follow() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 35: Camera Follow");

    Camera2D camera = {0};
    camera.target = (Vector2){0, 0};
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Vector2 player = {400, 225};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) player.x += 5;
        if (IsKeyDown(KEY_LEFT)) player.x -= 5;
        if (IsKeyDown(KEY_DOWN)) player.y += 5;
        if (IsKeyDown(KEY_UP)) player.y -= 5;

        camera.target = player;

        if (IsKeyDown(KEY_Z)) camera.zoom += 0.02f;
        if (IsKeyDown(KEY_X)) camera.zoom -= 0.02f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;

        if (IsKeyDown(KEY_Q)) camera.rotation -= 1;
        if (IsKeyDown(KEY_E)) camera.rotation += 1;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                for (int i = -1000; i <= 1000; i += 100)
                    DrawLine(i, -1000, i, 1000, LIGHTGRAY);
                for (int i = -1000; i <= 1000; i += 100)
                    DrawLine(-1000, i, 1000, i, LIGHTGRAY);

                DrawRectangleRec((Rectangle){player.x - 25, player.y - 25, 50, 50}, RED);
                DrawCircle((int)player.x, (int)player.y, 5, DARKGRAY);

                DrawText("World origin", 0, 0, 15, DARKGRAY);
            EndMode2D();

            DrawText("ARROWS: move  Q/E: rotate  Z/X: zoom", 50, 400, 20, DARKGRAY);
            DrawText(TextFormat("Zoom: %.2f  Rotation: %.0f", camera.zoom, camera.rotation), 50, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 35.1: Create a scrolling background with a camera that follows the player.
// Add a large tile grid and allow zooming with mouse wheel.
void challenge_scrolling_world() {
    std::cout << "Challenge 35.1 incomplete - fill in the TODOs!\n";

    // TODO: Create a Camera2D, WASD moves player, camera targets player
    // Zoom with mouse wheel: GetMouseWheelMove()
    // Draw grid lines in world space (use nested loops)
    // Camera.offset = {screenWidth/2, screenHeight/2} so player stays centered

    std::cout << "Hint: GetMouseWheelMove() > 0 means scroll up (zoom in)\n";
}

// CHALLENGE 35.2: Implement screen shake effect by jittering camera offset/rotation.
// Trigger with SPACE key.
void challenge_screen_shake() {
    std::cout << "Challenge 35.2 incomplete - fill in the TODOs!\n";

    // TODO: Camera2D with follow and zoom
    // float shakeIntensity = 0
    // On SPACE press: shakeIntensity = 10
    // Each frame: if shake > 0, apply random offset
    //   camera.offset.x += GetRandomValue(-shake, shake)
    //   shakeIntensity *= 0.9  (decay)

    std::cout << "Hint: Use GetRandomValue(-shakeIntensity, shakeIntensity) for jitter\n";
}

void exercise_camera_2d() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 35: Camera 2D\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_camera_follow();
    std::cout << "Example done.\n";
    challenge_scrolling_world();
    challenge_screen_shake();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 35 complete!\n";
    std::cout << "========================================\n";
}
