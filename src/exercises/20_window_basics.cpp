#include <raylib.h>
#include <iostream>
#include <string>

// ============================================================
// EXERCISE 20: Window & Basics
// ============================================================

// CONCEPT: raylib window management
// - InitWindow(width, height, title) creates the window
// - BeginDrawing()/EndDrawing() frame lifecycle
// - ClearBackground() sets the background color
// - DrawFPS() displays frames per second
// - CloseWindow() cleanly closes everything

void example_window_basics() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 20: Window & Basics");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangle(100, 100, 200, 150, RED);
            DrawCircle(500, 175, 80, BLUE);
            DrawRectangleLines(100, 300, 200, 80, GREEN);

            DrawFPS(10, 10);
            DrawText("Window & Basics - press ESC to exit", 200, 400, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 20.1: Change window size to 1024x768, change background to LIGHTGRAY,
// add a yellow triangle, and display window dimensions as text.
void challenge_window_properties() {
    std::cout << "Challenge 20.1 incomplete - fill in the TODOs!\n";

    const int screenWidth = 1024;  // TODO: change to 1280
    const int screenHeight = 768;  // TODO: change to 720

    // TODO: InitWindow with screenWidth, screenHeight, "Challenge 20.1"
    // TODO: SetTargetFPS(60)

    // TODO: Main loop with WindowShouldClose
    // Inside loop:
    //   ClearBackground with LIGHTGRAY (instead of RAYWHITE)
    //   Draw a yellow triangle using DrawTriangle
    //   Display window dimensions with TextFormat("Window: %dx%d", screenWidth, screenHeight)
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Use InitWindow, BeginDrawing/EndDrawing, ClearBackground, DrawTriangle, TextFormat\n";
}

void example_multiple_shapes() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 20: Multiple Shapes");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawCircle(150, 150, 100, ORANGE);
            DrawRectangle(300, 100, 150, 100, GREEN);
            DrawEllipse(600, 150, 100, 60, PURPLE);
            DrawRing((Vector2){200, 350}, 30, 60, 0, 270, 36, BLUE);
            DrawRectangleLinesEx((Rectangle){450, 300, 200, 100}, 4, MAROON);

            DrawFPS(10, 10);
            DrawText("Press ESC to exit", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 20.2: Draw a simple house using rectangles (walls) and triangles (roof).
// Add a circular window and rectangular door.
void challenge_draw_house() {
    std::cout << "Challenge 20.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 600, "Draw a House")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(SKYBLUE)
    //   Draw rectangle for house body (e.g., brown)
    //   Draw triangle for roof (e.g., dark red) using DrawTriangle
    //   Draw rectangle for door (e.g., brown)
    //   Draw circle for window (e.g., light blue with yellow border)
    //   DrawText with a label
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: SKYBLUE, BROWN, RED are predefined raylib colors\n";
}

void exercise_window_basics() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 20: Window & Basics\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_window_basics();
    std::cout << "Example 1 done.\n";
    challenge_window_properties();

    example_multiple_shapes();
    std::cout << "Example 2 done.\n";
    challenge_draw_house();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 20 complete!\n";
    std::cout << "========================================\n";
}
