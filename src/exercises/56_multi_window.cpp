#include "56_multi_window.h"
#include <raylib.h>
#include <iostream>
#include <vector>

// ============================================================
// EXERCISE 56: Multi-Window & Monitor Handling
// ============================================================

// CONCEPT: raylib supports a single window but can be moved
// across monitors, resized, and configured with various flags.
// - Monitor queries (count, resolution, name)
// - Window positioning and sizing
// - Fullscreen toggle and window flags
// - Multiple viewports within one window

void example_monitor_info() {
    const int monitorCount = GetMonitorCount();
    std::cout << "Detected " << monitorCount << " monitor(s):\n";
    for (int i = 0; i < monitorCount; i++) {
        std::cout << "  Monitor " << i << ": " << GetMonitorName(i) << "\n";
        std::cout << "    Resolution: " << GetMonitorWidth(i) << "x" << GetMonitorHeight(i) << "\n";
        std::cout << "    Position: (" << GetMonitorPosition(i).x << ", "
                  << GetMonitorPosition(i).y << ")\n";
        std::cout << "    Refresh Rate: " << GetMonitorRefreshRate(i) << " Hz\n";
        std::cout << "    Physical Size: " << GetMonitorPhysicalWidth(i) << "x"
                  << GetMonitorPhysicalHeight(i) << " mm\n";
    }
}

void example_window_management() {
    const int screenWidth = 640;
    const int screenHeight = 480;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Exercise 56: Window Management");

    // Move window to primary monitor center
    int monitor = 0;
    Vector2 monPos = GetMonitorPosition(monitor);
    int monWidth = GetMonitorWidth(monitor);
    int monHeight = GetMonitorHeight(monitor);
    SetWindowPosition(monPos.x + (monWidth - screenWidth) / 2,
                      monPos.y + (monHeight - screenHeight) / 2);

    bool fullscreen = false;
    float rotation = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_F)) {
            fullscreen = !fullscreen;
            if (fullscreen) {
                SetWindowState(FLAG_FULLSCREEN_MODE);
            } else {
                ClearWindowState(FLAG_FULLSCREEN_MODE);
            }
        }

        if (IsKeyPressed(KEY_M)) {
            monitor = (monitor + 1) % GetMonitorCount();
            Vector2 newPos = GetMonitorPosition(monitor);
            SetWindowPosition((int)newPos.x, (int)newPos.y);
        }

        if (IsKeyDown(KEY_LEFT)) rotation -= 90 * GetFrameTime();
        if (IsKeyDown(KEY_RIGHT)) rotation += 90 * GetFrameTime();

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw a shape that responds to window size
        int w = GetScreenWidth();
        int h = GetScreenHeight();

        DrawRectangle(w / 2 - 100, h / 2 - 100, 200, 200, DARKBLUE);
        DrawRectangleLines(w / 2 - 100, h / 2 - 100, 200, 200, BLUE);

        Vector2 center = {(float)w / 2, (float)h / 2};
        DrawRectanglePro({center.x - 30, center.y - 30, 60, 60},
                         {30, 30}, rotation, RED);

        DrawText(TextFormat("Window: %dx%d", w, h), 50, 50, 20, WHITE);
        DrawText(TextFormat("Monitor: %d (%s)", monitor, GetMonitorName(monitor)), 50, 75, 20, WHITE);
        DrawText("F: Toggle fullscreen", 50, h - 60, 15, GRAY);
        DrawText("M: Next monitor", 50, h - 40, 15, GRAY);
        DrawText("Left/Right: Rotate cube", 50, h - 20, 15, GRAY);

        DrawFPS(w - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 56.1: Implement a split-screen layout within the window.
// Divide the window into 2-4 viewports using rectangles.
void challenge_split_screen() {
    std::cout << "Challenge 56.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Divide the screen into 2 halves (left/right) or 4 quadrants
    //   Each viewport draws something different:
    //     - Top-left: 2D shapes
    //     - Top-right: colored gradient
    //     - Bottom-left: text display
    //     - Bottom-right: grid overlay
    //   Use BeginScissorMode() to clip each viewport

    std::cout << "Hint: Use BeginScissorMode(x, y, w, h) / EndScissorMode() for each viewport\n";
}

// CHALLENGE 56.2: Create a window with custom minimum/maximum sizes
// and opacity control. Let the user resize the window and adjust
// opacity with the mouse wheel.
void challenge_multi_window_properties() {
    std::cout << "Challenge 56.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   SetWindowMinSize(400, 300);
    //   SetWindowMaxSize(1200, 900);
    //   SetWindowOpacity(0.8f);
    //   Mouse wheel adjusts opacity between 0.5f and 1.0f
    //   Display current opacity value on screen

    std::cout << "Hint: GetMouseWheelMove() returns float, window should have FLAG_WINDOW_RESIZABLE\n";
}

void exercise_multi_window() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 56: Multi-Window & Monitor Handling\n";
    std::cout << "========================================\n\n";

    example_monitor_info();
    std::cout << "\nOpening window management demo - close to continue...\n\n";
    example_window_management();
    std::cout << "Window demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_split_screen();
    challenge_multi_window_properties();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 56 complete!\n";
    std::cout << "========================================\n";
}
