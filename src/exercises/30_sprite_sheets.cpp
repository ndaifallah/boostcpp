#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 30: Sprite Sheets
// ============================================================

// CONCEPT: sprite sheets in raylib
// - DrawTexturePro(texture, source, dest, origin, rotation, tint)
// - Source rect defines which part of the sheet to draw
// - Dest rect defines where/how to draw on screen
// - Used for animation: change source rect.x each frame
// - Also for tilemaps, UI sprites, etc.

void example_sprite_sheet_basics() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 30: Sprite Sheet Basics");

    Image img = GenImageChecked(128, 32, 16, 16, RED, BLUE);
    Texture2D sheet = LoadTextureFromImage(img);
    UnloadImage(img);

    Rectangle source = {0, 0, 16, 16};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 8; col++) {
                    source.x = col * 16;
                    source.y = row * 16;
                    Rectangle dest = {(float)(100 + col * 70), (float)(100 + row * 70), 64, 64};
                    DrawTexturePro(sheet, source, dest, (Vector2){0, 0}, 0, WHITE);
                }
            }

            DrawText("Sprite sheet frames", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(sheet);
    CloseWindow();
}

void example_animation() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 30: Animation");

    Image img = GenImageChecked(64, 32, 16, 16, GREEN, DARKGREEN);
    Texture2D runSheet = LoadTextureFromImage(img);
    UnloadImage(img);

    int numFrames = 4;
    int frameWidth = 16;
    int currentFrame = 0;
    float timer = 0;
    float frameDuration = 0.15f;

    Rectangle source = {0, 0, (float)frameWidth, 16};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        timer += GetFrameTime();
        if (timer >= frameDuration) {
            currentFrame = (currentFrame + 1) % numFrames;
            timer = 0;
        }

        source.x = (float)(currentFrame * frameWidth);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            Rectangle dest = {300, 175, 128, 128};
            DrawTexturePro(runSheet, source, dest, (Vector2){64, 64}, 0, WHITE);

            DrawText("Animated character (press SPACE to toggle speed)", 50, 50, 20, DARKGRAY);

            if (IsKeyPressed(KEY_SPACE)) {
                frameDuration = (frameDuration == 0.15f) ? 0.05f : 0.15f;
            }

            DrawText(TextFormat("Frame: %d/%d  Speed: %.2fs", currentFrame + 1, numFrames, frameDuration), 50, 80, 20, DARKGRAY);
            DrawFPS(10, 110);

        EndDrawing();
    }

    UnloadTexture(runSheet);
    CloseWindow();
}

// CHALLENGE 30.1: Create a sprite sheet texture at runtime (4x4 grid of colored squares)
// and use DrawTexturePro to display a specific "frame" from it.
// Allow arrow keys to navigate through frames.
void challenge_frame_navigation() {
    std::cout << "Challenge 30.1 incomplete - fill in the TODOs!\n";

    // TODO: Generate a 64x64 image divided into 4 frames of 16x16 each
    // Each frame should be a different color
    // Use GenImageColor + ImageDrawRectangle for each quadrant

    // Inside game loop:
    //   Use LEFT/RIGHT arrow keys to change current frame (0-3)
    //   source = {currentFrame * 16, 0, 16, 16}
    //   DrawTexturePro with source and a large dest rect
    //   Display current frame number

    // TODO: Cleanup

    std::cout << "Hint: Use IsKeyPressed(KEY_RIGHT) and IsKeyPressed(KEY_LEFT)\n";
}

// CHALLENGE 30.2: Implement a running animation by cycling through
// frames and moving the character horizontally across the screen.
void challenge_running_animation() {
    std::cout << "Challenge 30.2 incomplete - fill in the TODOs!\n";

    // TODO: Same sprite sheet approach but character moves right
    // float characterX = 0
    // float speed = 150  (pixels per second)

    // Inside game loop:
    //   characterX += speed * GetFrameTime()
    //   if characterX > screenWidth: characterX = -128
    //   Cycle through frames for animation
    //   DrawTexturePro at characterX with the current frame source rect

    // TODO: Cleanup

    std::cout << "Hint: Combine scrolling position + frame animation cycling\n";
}

void exercise_sprite_sheets() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 30: Sprite Sheets\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_sprite_sheet_basics();
    std::cout << "Example 1 done.\n";
    example_animation();
    std::cout << "Example 2 done.\n";
    challenge_frame_navigation();
    challenge_running_animation();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 30 complete!\n";
    std::cout << "========================================\n";
}
