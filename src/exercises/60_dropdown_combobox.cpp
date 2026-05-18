#include "60_dropdown_combobox.h"
#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>

// ============================================================
// EXERCISE 60: Dropdown & Combo Box UI
// ============================================================

// CONCEPT: custom dropdown/combobox widget built with raylib
// - No external GUI library (raygui not included)
// - Uses rectangles, text, and mouse detection
// - State management: open/closed, hovered item, selected item

struct Dropdown {
    Rectangle bounds;
    std::vector<std::string> items;
    int selected;
    bool open;
    int hovered;
};

void drawDropdown(Dropdown &dd) {
    // Main button
    DrawRectangleRec(dd.bounds, dd.open ? DARKBLUE : DARKGRAY);
    DrawRectangleLinesEx(dd.bounds, 2, WHITE);

    const char *label = dd.selected >= 0 ? dd.items[dd.selected].c_str() : "Select...";
    DrawText(label, (int)dd.bounds.x + 10, (int)dd.bounds.y + 8, 16, WHITE);

    // Arrow indicator
    DrawTriangle(
        {dd.bounds.x + dd.bounds.width - 20, dd.bounds.y + 10},
        {dd.bounds.x + dd.bounds.width - 10, dd.bounds.y + 10},
        dd.open
            ? Vector2{dd.bounds.x + dd.bounds.width - 15, dd.bounds.y + 4}
            : Vector2{dd.bounds.x + dd.bounds.width - 15, dd.bounds.y + 16},
        WHITE);

    if (dd.open) {
        float itemHeight = 24;
        for (size_t i = 0; i < dd.items.size(); i++) {
            Rectangle itemBounds = {
                dd.bounds.x,
                dd.bounds.y + dd.bounds.height + i * itemHeight,
                dd.bounds.width,
                itemHeight
            };
            Color bg = (i == (size_t)dd.hovered) ? BLUE : DARKBLUE;
            Color border = (i == (size_t)dd.selected) ? YELLOW : GRAY;
            DrawRectangleRec(itemBounds, bg);
            DrawRectangleLinesEx(itemBounds, 1, border);
            DrawText(dd.items[i].c_str(),
                     (int)itemBounds.x + 8,
                     (int)itemBounds.y + 4,
                     14, WHITE);
        }
    }
}

void example_dropdown() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 60: Dropdown & Combo Box");

    Dropdown dd;
    dd.bounds = {250, 150, 200, 32};
    dd.items = {"Easy", "Medium", "Hard", "Expert", "Nightmare"};
    dd.selected = -1;
    dd.open = false;
    dd.hovered = -1;

    std::vector<Color> themeColors = {GREEN, BLUE, RED, PURPLE, MAROON};
    Color bgColor = DARKGRAY;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        // Update hover state
        dd.hovered = -1;
        if (dd.open) {
            float itemHeight = 24;
            for (size_t i = 0; i < dd.items.size(); i++) {
                Rectangle itemBounds = {
                    dd.bounds.x,
                    dd.bounds.y + dd.bounds.height + i * itemHeight,
                    dd.bounds.width,
                    itemHeight
                };
                if (CheckCollisionPointRec(mouse, itemBounds)) {
                    dd.hovered = (int)i;
                    break;
                }
            }
        }

        // Mouse click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, dd.bounds)) {
                dd.open = !dd.open;
            } else if (dd.open && dd.hovered >= 0) {
                dd.selected = dd.hovered;
                dd.open = false;
                bgColor = themeColors[dd.selected];
            } else {
                dd.open = false;
            }
        }

        BeginDrawing();
        ClearBackground(bgColor);

        DrawText("Exercise 60: Dropdown / Combo Box", 50, 40, 20, WHITE);
        DrawText("Click to open, select a difficulty", 50, 70, 15, GRAY);

        drawDropdown(dd);

        if (dd.selected >= 0) {
            DrawText(TextFormat("Selected: %s", dd.items[dd.selected].c_str()),
                     250, 300, 20, YELLOW);
        }

        // Draw a simple checkboxes
        DrawText("Settings:", 50, 200, 18, WHITE);
        static bool optionA = true, optionB = false, optionC = true;
        Rectangle cbA = {50, 230, 20, 20};
        Rectangle cbB = {50, 260, 20, 20};
        Rectangle cbC = {50, 290, 20, 20};

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, cbA)) optionA = !optionA;
            if (CheckCollisionPointRec(mouse, cbB)) optionB = !optionB;
            if (CheckCollisionPointRec(mouse, cbC)) optionC = !optionC;
        }

        auto drawCheckbox = [](Rectangle r, bool checked, const char *label) {
            DrawRectangleRec(r, checked ? GREEN : DARKGRAY);
            DrawRectangleLinesEx(r, 2, WHITE);
            if (checked) {
                DrawText("X", (int)r.x + 4, (int)r.y + 1, 16, WHITE);
            }
            DrawText(label, (int)r.x + 30, (int)r.y + 2, 16, LIGHTGRAY);
        };

        drawCheckbox(cbA, optionA, "Fullscreen");
        drawCheckbox(cbB, optionB, "VSync");
        drawCheckbox(cbC, optionC, "Sound FX");

        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 60.1: Add keyboard navigation to the dropdown.
// Up/Down arrows change hovered item, Enter/Space confirm selection.
void challenge_keyboard_dropdown() {
    std::cout << "Challenge 60.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   When dropdown is open:
    //     KEY_DOWN: hovered = (hovered + 1) % items.size()
    //     KEY_UP: hovered = (hovered - 1 + items.size()) % items.size()
    //     KEY_ENTER: select the hovered item and close
    //   When dropdown is closed:
    //     KEY_SPACE: open the dropdown (if focused)

    std::cout << "Hint: Use IsKeyPressed() checks in the update section\n";
}

// CHALLENGE 60.2: Implement a multi-select combo box where the user
// can toggle multiple options on/off (like a filter list).
void challenge_multiselect() {
    std::cout << "Challenge 60.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Use a vector<bool> for selection state per item
    //   Clicking an item toggles it on/off (instead of single select)
    //   Display selected items as tags/chips below the dropdown
    //   Example items: "Filter A", "Filter B", "Filter C", "Filter D"

    std::cout << "Hint: Draw selected items as rounded rectangles with labels\n";
}

void exercise_dropdown_combobox() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 60: Dropdown & Combo Box UI\n";
    std::cout << "========================================\n";
    std::cout << "Opening UI demo - close window to continue...\n\n";

    example_dropdown();
    std::cout << "UI demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_keyboard_dropdown();
    challenge_multiselect();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 60 complete!\n";
    std::cout << "========================================\n";
}
