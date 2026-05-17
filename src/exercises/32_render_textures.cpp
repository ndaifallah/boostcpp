#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 32: Render Textures
// ============================================================

// CONCEPT: render textures (off-screen rendering)
// - LoadRenderTexture(width, height): create off-screen target
// - BeginTextureMode(target): draw to off-screen buffer
// - EndTextureMode(): return to main screen
// - target.texture: the resulting Texture2D to draw
// - Useful for: post-processing, minimaps, caching complex scenes
// - UnloadRenderTexture(target): cleanup

void example_offscreen_rendering() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 32: Render Textures");

    RenderTexture2D target = LoadRenderTexture(400, 225);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);

            DrawCircle(200, 112, 80, BLUE);
            DrawRectangle(50, 50, 100, 100, RED);
            DrawTriangle((Vector2){300, 30}, (Vector2){350, 180}, (Vector2){250, 180}, GREEN);
            DrawText("Off-screen", 140, 100, 20, DARKGRAY);

        EndTextureMode();

        BeginDrawing();
            ClearBackground(DARKGRAY);

            DrawTextureRec(target.texture, (Rectangle){0, 0, 400, -225}, (Vector2){200, 112}, WHITE);
            DrawRectangleLines(200, 112, 400, 225, YELLOW);

            DrawText("Main screen - Press ESC to exit", 50, 400, 20, RAYWHITE);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
}

void example_render_texture_effects() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 32: Effects with Render Textures");

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    float time = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        time += GetFrameTime();

        BeginTextureMode(target);
            ClearBackground(Fade(RAYWHITE, 0.1f));

            float x = 400 + cos(time) * 200;
            float y = 225 + sin(time * 1.3f) * 100;
            DrawCircle((int)x, (int)y, 15, Fade(RED, 0.3f));

            x = 400 + sin(time * 0.7f) * 250;
            y = 225 + cos(time * 1.1f) * 120;
            DrawCircle((int)x, (int)y, 10, Fade(BLUE, 0.3f));

        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);

            DrawTextureRec(target.texture, (Rectangle){0, 0, (float)screenWidth, (float)-screenHeight}, (Vector2){0, 0}, WHITE);
            DrawText("Trail effect with RenderTexture", 50, 50, 20, WHITE);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
}

// CHALLENGE 32.1: Draw a complex scene (house, trees, sun) to a render texture
// once, then display it on the main screen with a pulsating color overlay.
// This avoids re-drawing the complex scene each frame.
void challenge_complex_scene_caching() {
    std::cout << "Challenge 32.1 incomplete - fill in the TODOs!\n";

    // TODO: Create a RenderTexture2D
    // Draw once (outside game loop): background, sun, house, trees, etc.
    // Inside game loop: DrawTextureRec the cached render texture
    // Add a pulsating colored rectangle on top with low alpha

    std::cout << "Hint: Draw complex scene in BeginTextureMode/EndTextureMode once\n";
}

// CHALLENGE 32.2: Create a magnifying glass effect using a render texture.
// Draw the normal scene, then draw a magnified portion in a circle overlay.
void challenge_magnify() {
    std::cout << "Challenge 32.2 incomplete - fill in the TODOs!\n";

    // TODO: Draw a grid of text/shapes on screen
    // Inside game loop, get mouse position
    // Use a render texture or DrawTexturePro with source rect to show a magnified view
    // Draw a circle that shows the magnified content

    std::cout << "Hint: DrawTexturePro with a small source and large dest creates zoom\n";
}

void exercise_render_textures() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 32: Render Textures\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_offscreen_rendering();
    std::cout << "Example 1 done.\n";
    example_render_texture_effects();
    std::cout << "Example 2 done.\n";
    challenge_complex_scene_caching();
    challenge_magnify();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 32 complete!\n";
    std::cout << "========================================\n";
}
