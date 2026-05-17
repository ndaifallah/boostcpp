#include <raylib.h>
#include <iostream>
#include <cstring>

// ============================================================
// EXERCISE 24: Text & Fonts
// ============================================================

// CONCEPT: text rendering in raylib
// - DrawText(text, x, y, fontSize, color): simple text
// - TextFormat(format, ...): formatted string
// - MeasureText(text, fontSize): width in pixels
// - LoadFont(path): load a TTF font
// - DrawTextEx(font, text, position, fontSize, spacing, color): with custom font
// - GetFontDefault(): default raylib font

void example_basic_text() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 24: Basic Text");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Hello, raylib!", 50, 50, 40, DARKBLUE);
            DrawText("Small text", 50, 110, 20, GRAY);
            DrawText("MEDIUM TEXT", 50, 150, 30, MAROON);
            DrawText("LARGE TEXT", 50, 200, 50, PURPLE);

            const char* formatted = TextFormat("FPS: %i", GetFPS());
            DrawText(formatted, 50, 280, 20, DARKGREEN);

            const char* mousePos = TextFormat("Mouse: (%i, %i)",
                GetMouseX(), GetMouseY());
            DrawText(mousePos, 50, 310, 20, DARKGRAY);

            const char* screenInfo = TextFormat("Screen: %dx%d",
                screenWidth, screenHeight);
            DrawText(screenInfo, 50, 340, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

void example_font_loading() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 24: Custom Fonts");

    Font defaultFont = GetFontDefault();
    Font customFont = {0};

    if (FileExists("/System/Library/Fonts/Helvetica.ttc")) {
        customFont = LoadFont("/System/Library/Fonts/Helvetica.ttc");
    } else if (FileExists("/System/Library/Fonts/Helvetica.ttf")) {
        customFont = LoadFont("/System/Library/Fonts/Helvetica.ttf");
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTextEx(defaultFont, "Default Font", (Vector2){50, 50}, 40, 2, DARKGRAY);
            DrawTextEx(defaultFont, "With custom spacing", (Vector2){50, 100}, 24, 8, GRAY);

            if (customFont.texture.id > 0) {
                DrawTextEx(customFont, "Custom Font (Helvetica)", (Vector2){50, 180}, 36, 2, DARKBLUE);
                DrawTextEx(customFont, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", (Vector2){50, 230}, 20, 1, GRAY);
                DrawTextEx(customFont, "abcdefghijklmnopqrstuvwxyz", (Vector2){50, 260}, 20, 1, GRAY);
                DrawTextEx(customFont, "0123456789", (Vector2){50, 290}, 20, 1, GRAY);
            } else {
                DrawText("Custom font not available", 50, 180, 20, RED);
            }

            DrawText("Press ESC to exit", 50, 380, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    if (customFont.texture.id > 0) UnloadFont(customFont);
    CloseWindow();
}

// CHALLENGE 24.1: Create a scrolling text marquee that moves from right to left.
void challenge_scrolling_marquee() {
    std::cout << "Challenge 24.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 200, "Scrolling Marquee")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(BLACK)
    //   Use a variable "offset" that decreases over time (scroll right to left)
    //   DrawText at (offset, 80) with text "*** BREAKING NEWS: raylib is awesome! ***"
    //   When offset is less than -textWidth, reset to screenWidth (or use modulus)
    //   Use MeasureText to get the text width
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Use GetFrameTime() to update offset smoothly\n";
}

// CHALLENGE 24.2: Display the alphabet as a colorful word cloud.
// Each letter should have a different color and slightly different position/font size.
void challenge_alphabet_wordcloud() {
    std::cout << "Challenge 24.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 400, "Alphabet Word Cloud")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(RAYWHITE)
    //   For letters A-Z (use TextFormat to produce each letter):
    //     Draw each letter at a different position with random-ish color and size
    //     You can use (i * spacing) for x-position
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: TextFormat(\"%c\", 'A' + i) gives each letter\n";
}

void exercise_text_fonts() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 24: Text & Fonts\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_basic_text();
    std::cout << "Example 1 done.\n";
    example_font_loading();
    std::cout << "Example 2 done.\n";
    challenge_scrolling_marquee();
    challenge_alphabet_wordcloud();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 24 complete!\n";
    std::cout << "========================================\n";
}
