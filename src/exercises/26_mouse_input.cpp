#include <raylib.h>
#include <iostream>
#include <vector>

// ============================================================
// EXERCISE 26: Mouse Input
// ============================================================

// CONCEPT: mouse input in raylib
// - GetMouseX(), GetMouseY(): cursor position
// - GetMousePosition(): returns Vector2
// - IsMouseButtonPressed(button): once on press
// - IsMouseButtonDown(button): while held
// - IsMouseButtonReleased(button): once on release
// - GetMouseWheelMove(): returns float delta
// - SetMouseCursor(cursor): change cursor style
// - ShowCursor() / HideCursor()

void example_mouse_basics() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 26: Mouse Basics");

    SetTargetFPS(60);

    Vector2 mousePos = {0, 0};
    bool leftDown = false, rightDown = false;

    while (!WindowShouldClose()) {
        mousePos = GetMousePosition();
        leftDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        rightDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawCircleV(mousePos, 20, leftDown ? RED : GRAY);
            if (rightDown) DrawCircleLines(mousePos.x, mousePos.y, 25, BLUE);

            DrawText(TextFormat("Mouse Position: (%.0f, %.0f)", mousePos.x, mousePos.y), 50, 50, 20, DARKGRAY);
            DrawText(TextFormat("Left button: %s", leftDown ? "DOWN" : "up"), 50, 80, 20, leftDown ? RED : DARKGRAY);
            DrawText(TextFormat("Right button: %s", rightDown ? "DOWN" : "up"), 50, 110, 20, rightDown ? BLUE : DARKGRAY);
            DrawText(TextFormat("Wheel: %.1f", GetMouseWheelMove()), 50, 140, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void example_mouse_interaction() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 26: Mouse Interaction");

    SetTargetFPS(60);

    Rectangle button = {300, 175, 200, 100};
    int clickCount = 0;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool hover = CheckCollisionPointRec(mouse, button);

        if (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            clickCount++;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangleRec(button, hover ? SKYBLUE : LIGHTGRAY);
            DrawRectangleLinesEx(button, 2, hover ? DARKBLUE : GRAY);
            DrawText("Click me!", 355, 215, 20, hover ? WHITE : DARKGRAY);

            DrawText(TextFormat("Clicks: %d", clickCount), 320, 300, 30, MAROON);
            DrawText("Press R to reset", 330, 350, 20, DARKGRAY);

            if (IsKeyPressed(KEY_R)) clickCount = 0;

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 26.1: Implement drag-and-drop of a rectangle.
void challenge_drag_and_drop() {
    std::cout << "Challenge 26.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 450, "Drag and Drop")
    // Init a Rectangle (e.g., {200, 175, 100, 100})
    // bool dragging = false
    // Vector2 offset = {0, 0}
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   Get mouse position
    //   If IsMouseButtonPressed(LEFT) and CheckCollisionPointRec(mouse, rect):
    //     dragging = true, store offset
    //   If IsMouseButtonReleased(LEFT): dragging = false
    //   If dragging: rect.x = mouse.x - offset.x, rect.y = mouse.y - offset.y
    //   Clamp rect to screen bounds
    //   ClearBackground, draw rect (different color when dragging), instructions, FPS

    // TODO: CloseWindow

    std::cout << "Hint: offset = (mouse.x - rect.x, mouse.y - rect.y) when starting drag\n";
}

// CHALLENGE 26.2: Create a simple drawing app where the user can draw
// freeform lines with the mouse (hold left button to draw).
void challenge_drawing_app() {
    std::cout << "Challenge 26.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 450, "Drawing App")
    // Store points in a std::vector<Vector2>
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   If IsMouseButtonDown(LEFT):
    //     Push current mouse position to points vector
    //   If IsKeyPressed(KEY_C): clear points
    //   ClearBackground(WHITE)
    //   Draw all points as connected lines (or small circles for dots)
    //   Show clear instructions, point count, FPS

    // TODO: CloseWindow

    std::cout << "Hint: Use DrawLineEx between consecutive points for smooth lines\n";
}

void exercise_mouse_input() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 26: Mouse Input\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_mouse_basics();
    std::cout << "Example 1 done.\n";
    example_mouse_interaction();
    std::cout << "Example 2 done.\n";
    challenge_drag_and_drop();
    challenge_drawing_app();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 26 complete!\n";
    std::cout << "========================================\n";
}
