#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 21: Colors & Blending
// ============================================================

// CONCEPT: raylib colors
// - Color struct: {r, g, b, a} unsigned chars
// - Predefined colors: RAYWHITE, RED, BLUE, GREEN, etc.
// - Fade(color, alpha) for transparency
// - ColorAlpha(color, alpha) for per-color alpha
// - ColorAlphaBlend(dst, src) for manual blending
// - GetColor(hex) to create from hex value

void example_basic_colors() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 21: Basic Colors");

    SetTargetFPS(60);

    Color customOrange = {255, 165, 0, 255};
    Color customPink = GetColor(0xFF69B4FF);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(50, 50, 150, 100, RED);
            DrawRectangle(250, 50, 150, 100, GREEN);
            DrawRectangle(450, 50, 150, 100, BLUE);
            DrawRectangle(50, 200, 150, 100, customOrange);
            DrawRectangle(250, 200, 150, 100, customPink);
            DrawRectangle(450, 200, 150, 100, PURPLE);

            DrawText("RED", 100, 160, 20, DARKGRAY);
            DrawText("GREEN", 295, 160, 20, DARKGRAY);
            DrawText("BLUE", 505, 160, 20, DARKGRAY);
            DrawText("Orange (custom)", 55, 310, 20, DARKGRAY);
            DrawText("Pink (hex)", 285, 310, 20, DARKGRAY);
            DrawText("PURPLE", 490, 310, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void example_alpha_blending() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 21: Alpha Blending");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(100, 100, 200, 200, RED);
            DrawRectangle(180, 50, 200, 200, Fade(BLUE, 0.3f));
            DrawRectangle(260, 150, 200, 200, Fade(GREEN, 0.5f));

            DrawRectangle(500, 50, 100, 100, ColorAlpha(RED, 0.2f));
            DrawRectangle(550, 80, 100, 100, ColorAlpha(RED, 0.5f));
            DrawRectangle(600, 110, 100, 100, ColorAlpha(RED, 0.8f));

            DrawText("Alpha blending", 100, 350, 20, DARKGRAY);
            DrawText("0.2  0.5  0.8", 520, 220, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 21.1: Create a horizontal rainbow gradient bar using ColorAlphaBlend
// or by manually setting Color values. Draw 10+ rectangles of different hues.
void challenge_rainbow_gradient() {
    std::cout << "Challenge 21.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 200, "Rainbow Gradient")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(RAYWHITE)
    //   Draw 10 or more adjacent rectangles from left to right
    //   Each rectangle should have a different hue (red, orange, yellow, green, blue, indigo, violet)
    //   DrawFPS, then draw "Rainbow Gradient" text at bottom

    // TODO: CloseWindow

    std::cout << "Hint: Manually set Color r/g/b values to create color transitions\n";
}

// CHALLENGE 21.2: Draw overlapping circles with different alpha values
// to demonstrate additive color blending visually.
void challenge_color_wheel() {
    std::cout << "Challenge 21.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 600, "Overlapping Colors")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(BLACK)
    //   Draw 3 large circles in a triangle layout (red, green, blue)
    //   Use Fade() with alpha ~0.3-0.4 so they blend
    //   The overlaps should create cyan, magenta, yellow
    //   DrawFPS and a title

    // TODO: CloseWindow

    std::cout << "Hint: RED+GREEN=YELLOW, RED+BLUE=MAGENTA, GREEN+BLUE=CYAN\n";
}

void exercise_colors_blending() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 21: Colors & Blending\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_basic_colors();
    std::cout << "Example 1 done.\n";
    example_alpha_blending();
    std::cout << "Example 2 done.\n";
    challenge_rainbow_gradient();
    challenge_color_wheel();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 21 complete!\n";
    std::cout << "========================================\n";
}
