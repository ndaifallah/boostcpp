#include "59_gesture_detection.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 59: Gesture Detection (touch, swipe, pinch)
// ============================================================

// CONCEPT: raylib supports touch gestures on mobile and desktop
// - GESTURE_TAP, GESTURE_DOUBLETAP
// - GESTURE_SWIPE_*, GESTURE_DRAG
// - GESTURE_PINCH_IN/OUT for zoom
// - Works with mouse on desktop (drag = click + move)

void example_gestures() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Exercise 59: Gesture Detection");

    SetGesturesEnabled(GESTURE_TAP | GESTURE_DOUBLETAP |
                       GESTURE_DRAG | GESTURE_SWIPE_UP |
                       GESTURE_SWIPE_DOWN | GESTURE_SWIPE_LEFT |
                       GESTURE_SWIPE_RIGHT | GESTURE_PINCH_IN |
                       GESTURE_PINCH_OUT);

    Vector2 pos = {(float)screenWidth / 2, (float)screenHeight / 2};
    float size = 50;
    Color shapeColor = RED;
    float rotation = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        int gesture = GetGestureDetected();

        switch (gesture) {
            case GESTURE_TAP:
                shapeColor = GREEN;
                break;
            case GESTURE_DOUBLETAP:
                shapeColor = BLUE;
                break;
            case GESTURE_DRAG: {
                Vector2 drag = GetGestureDragVector();
                pos.x += drag.x * 0.5f;
                pos.y += drag.y * 0.5f;
                shapeColor = ORANGE;
                break;
            }
            case GESTURE_SWIPE_UP:
                pos.y -= 30;
                shapeColor = YELLOW;
                break;
            case GESTURE_SWIPE_DOWN:
                pos.y += 30;
                shapeColor = PURPLE;
                break;
            case GESTURE_SWIPE_LEFT:
                pos.x -= 30;
                shapeColor = SKYBLUE;
                break;
            case GESTURE_SWIPE_RIGHT:
                pos.x += 30;
                shapeColor = PINK;
                break;
            case GESTURE_PINCH_IN:
                size = fmaxf(10, size - 5);
                shapeColor = RED;
                break;
            case GESTURE_PINCH_OUT:
                size = fminf(200, size + 5);
                shapeColor = MAGENTA;
                break;
            default:
                shapeColor = LIGHTGRAY;
                break;
        }

        // Clamp position
        pos.x = Clamp(pos.x, size, GetScreenWidth() - size);
        pos.y = Clamp(pos.y, size, GetScreenHeight() - size);

        rotation += 1;

        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawRectanglePro({pos.x, pos.y, size, size},
                         {size / 2, size / 2}, rotation, shapeColor);
        DrawRectangleLinesEx({pos.x - size / 2, pos.y - size / 2, size, size},
                             2, WHITE);

        // Draw gesture info
        const char *gestureNames[] = {
            "NONE", "TAP", "DOUBLETAP", "HOLD", "DRAG",
            "SWIPE_RIGHT", "SWIPE_LEFT", "SWIPE_UP", "SWIPE_DOWN",
            "PINCH_IN", "PINCH_OUT"
        };
        DrawText(TextFormat("Gesture: %s", gestureNames[gesture < 10 ? gesture : 0]),
                 50, 30, 25, WHITE);
        DrawText(TextFormat("Pos: (%.0f, %.0f)", pos.x, pos.y), 50, 60, 20, LIGHTGRAY);
        DrawText(TextFormat("Size: %.0f", size), 50, 85, 20, LIGHTGRAY);

        if (gesture == GESTURE_DRAG) {
            Vector2 drag = GetGestureDragVector();
            DrawText(TextFormat("Drag: (%.1f, %.1f)", drag.x, drag.y), 50, 110, 15, GRAY);
        }
        if (gesture == GESTURE_PINCH_IN || gesture == GESTURE_PINCH_OUT) {
            DrawText(TextFormat("Pinch angle: %.1f", GetGesturePinchAngle()), 50, 110, 15, GRAY);
        }

        DrawText("Touch/drag the square or use gestures!", 50, GetScreenHeight() - 40, 15, GRAY);

        DrawFPS(GetScreenWidth() - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 59.1: Create a drawing app where the user can draw
// lines with their finger/mouse. Track drag path with a vector of points.
void challenge_gesture_drawing() {
    std::cout << "Challenge 59.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   std::vector<Vector2> points
    //   On GESTURE_DRAG: add current touch position to points
    //   Draw lines between consecutive points
    //   Clear with right-click or keyboard C

    std::cout << "Hint: Use GetTouchPosition(0) or GetMousePosition() for current pos\n";
}

// CHALLENGE 59.2: Implement pinch-to-zoom on a procedurally
// generated mandelbrot or grid pattern.
void challenge_pinch_zoom() {
    std::cout << "Challenge 59.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Draw a large grid or fractal
    //   On PINCH_IN: zoom out (scale *= 0.9)
    //   On PINCH_OUT: zoom in (scale *= 1.1)
    //   Use offset to pan (drag gesture)
    //   Display current zoom level

    std::cout << "Hint: Use a Matrix transform or manually scale drawn objects\n";
}

void exercise_gesture_detection() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 59: Gesture Detection\n";
    std::cout << "========================================\n";
    std::cout << "Opening gesture demo - close window to continue...\n\n";

    example_gestures();
    std::cout << "Gesture demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_gesture_drawing();
    challenge_pinch_zoom();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 59 complete!\n";
    std::cout << "========================================\n";
}
