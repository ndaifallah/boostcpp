#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <string>

// ============================================================
// EXERCISE 45: UI Elements
// ============================================================

// CONCEPT: building custom UI in raylib
// - raylib has no built-in GUI system (raygui is separate)
// - Build UI elements from rectangles, text, and mouse input
// - Button: CheckCollisionPointRec + IsMouseButtonPressed
// - Slider: drag to change a value
// - Checkbox: toggle state on click
// - Hot-render: draw everything each frame (immediate mode)

struct Button {
    Rectangle bounds;
    const char* text;
    Color normalColor;
    Color hoverColor;
    Color textColor;
};

bool draw_button(Button btn) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, btn.bounds);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    DrawRectangleRec(btn.bounds, hover ? btn.hoverColor : btn.normalColor);
    DrawRectangleLinesEx(btn.bounds, 2, DARKGRAY);

    float textW = MeasureText(btn.text, 20);
    float textX = btn.bounds.x + (btn.bounds.width - textW) / 2;
    float textY = btn.bounds.y + (btn.bounds.height - 20) / 2;
    DrawText(btn.text, (int)textX, (int)textY, 20, btn.textColor);

    return clicked;
}

float draw_slider(Rectangle bounds, float value, float minVal, float maxVal) {
    Vector2 mouse = GetMousePosition();
    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawRectangleLinesEx(bounds, 2, DARKGRAY);

    float range = maxVal - minVal;
    float fillW = (value - minVal) / range * bounds.width;
    DrawRectangle(bounds.x, bounds.y, (int)fillW, (int)bounds.height, SKYBLUE);

    float knobX = bounds.x + fillW;
    Rectangle knob = {knobX - 5, bounds.y - 2, 10, bounds.height + 4};

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(mouse, bounds) || CheckCollisionPointRec(mouse, knob)) {
            float newFill = (mouse.x - bounds.x) / bounds.width;
            value = Clamp(minVal + newFill * range, minVal, maxVal);
        }
    }

    DrawRectangleRec(knob, DARKBLUE);

    return value;
}

bool draw_checkbox(Rectangle bounds, bool checked, const char* label) {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, bounds);
    bool clicked = hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    DrawRectangleRec(bounds, checked ? GREEN : WHITE);
    DrawRectangleLinesEx(bounds, 2, DARKGRAY);

    if (checked) {
        DrawText("X", (int)(bounds.x + 4), (int)(bounds.y + 2), 20, DARKGREEN);
    }

    DrawText(label, (int)(bounds.x + bounds.width + 10), (int)(bounds.y + 2), 20, DARKGRAY);

    if (clicked) return !checked;
    return checked;
}

void example_ui_demo() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 45: UI Elements");

    Button btn1 = {{300, 100, 200, 50}, "Click Me!", LIGHTGRAY, SKYBLUE, DARKGRAY};
    Button btn2 = {{300, 180, 200, 50}, "Reset", LIGHTGRAY, PINK, DARKGRAY};

    float sliderValue = 50.0f;
    bool checkboxChecked = true;
    int clickCount = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (draw_button(btn1)) clickCount++;
        if (draw_button(btn2)) { clickCount = 0; sliderValue = 50.0f; checkboxChecked = true; }

        sliderValue = draw_slider({300, 280, 200, 20}, sliderValue, 0, 100);
        checkboxChecked = draw_checkbox({300, 330, 25, 25}, checkboxChecked, "Enable feature");

        BeginDrawing();
            DrawText("UI Elements Demo", 300, 50, 25, DARKGRAY);
            DrawText(TextFormat("Clicks: %d", clickCount), 50, 150, 20, DARKGRAY);
            DrawText(TextFormat("Slider: %.1f", sliderValue), 50, 280, 20, DARKGRAY);
            DrawText(TextFormat("Checkbox: %s", checkboxChecked ? "ON" : "OFF"), 50, 330, 20, DARKGRAY);

            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 45.1: Create a color picker with 3 sliders (R, G, B).
// Display the resulting color in a preview rectangle.
void challenge_color_picker() {
    std::cout << "Challenge 45.1 incomplete - fill in the TODOs!\n";

    // TODO: 3 sliders for R, G, B values (0-255 each)
    // Preview rectangle showing the combined color
    // Display hex value (e.g., "#FFA500")

    std::cout << "Hint: Draw 3 draw_slider calls, set color = {r, g, b, 255}\n";
}

// CHALLENGE 45.2: Build a simple settings menu with:
// - Fullscreen toggle (checkbox)
// - Volume slider (0-100)
// - Resolution selector (buttons cycling through options)
void challenge_settings_menu() {
    std::cout << "Challenge 45.2 incomplete - fill in the TODOs!\n";

    // TODO: Fullscreen checkbox
    // Volume slider
    // Resolution buttons (800x600, 1024x768, 1280x720, 1920x1080)
    // Display current settings

    std::cout << "Hint: Use ToggleFullscreen() for fullscreen toggle\n";
}

void exercise_ui_elements() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 45: UI Elements\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_ui_demo();
    std::cout << "Example done.\n";
    challenge_color_picker();
    challenge_settings_menu();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 45 complete!\n";
    std::cout << "========================================\n";
}
