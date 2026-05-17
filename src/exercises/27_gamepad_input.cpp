#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>

// ============================================================
// EXERCISE 27: Gamepad Input
// ============================================================

// CONCEPT: gamepad/controller input in raylib
// - IsGamepadAvailable(gamepad): check if connected
// - GetGamepadName(gamepad): get controller name
// - IsGamepadButtonPressed(gamepad, button): once on press
// - IsGamepadButtonDown(gamepad, button): while held
// - GetGamepadAxisMovement(gamepad, axis): analog value [-1..1]
// - 0: pre-defined player slot (0)
// - Button and axis constants: GAMEPAD_BUTTON_RIGHT_FACE_DOWN, GAMEPAD_AXIS_LEFT_X, etc.

void example_gamepad_detection() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 27: Gamepad Detection");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            bool gamepadAvailable = IsGamepadAvailable(0);

            if (gamepadAvailable) {
                const char* name = GetGamepadName(0);
                DrawText(TextFormat("Gamepad detected: %s", name), 50, 50, 25, GREEN);
                DrawText("Press buttons on your controller!", 50, 100, 20, DARKGRAY);

                int y = 140;
                for (int btn = 0; btn < 16; btn++) {
                    bool pressed = IsGamepadButtonPressed(0, btn);
                    bool held = IsGamepadButtonDown(0, btn);
                    Color c = held ? GREEN : (pressed ? ORANGE : LIGHTGRAY);
                    DrawText(TextFormat("Button %2d: %s", btn, held ? "DOWN" : (pressed ? "PRESS" : "up")), 50, y, 15, c);
                    y += 20;
                }

                DrawText(TextFormat("Axis LX: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X)), 500, 140, 15, DARKGRAY);
                DrawText(TextFormat("Axis LY: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y)), 500, 160, 15, DARKGRAY);
                DrawText(TextFormat("Axis RX: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X)), 500, 180, 15, DARKGRAY);
                DrawText(TextFormat("Axis RY: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y)), 500, 200, 15, DARKGRAY);
                DrawText(TextFormat("L Trigger: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_TRIGGER)), 500, 220, 15, DARKGRAY);
                DrawText(TextFormat("R Trigger: %.2f", GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_TRIGGER)), 500, 240, 15, DARKGRAY);
            } else {
                DrawText("No gamepad detected!", 50, 50, 30, RED);
                DrawText("Connect a controller and press any button", 50, 100, 20, DARKGRAY);
                DrawText("(or press ESC to skip this example)", 50, 140, 20, DARKGRAY);
            }

            DrawFPS(10, 10);
            DrawText("Exercise 27: Gamepad Input - ESC to exit", 200, 400, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void example_joystick_movement() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 27: Joystick Movement");

    SetTargetFPS(60);

    float playerX = 400, playerY = 225;
    float speed = 5.0f;
    const float deadzone = 0.2f;

    while (!WindowShouldClose()) {
        if (IsGamepadAvailable(0)) {
            float lx = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
            float ly = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

            if (fabs(lx) > deadzone) playerX += lx * speed;
            if (fabs(ly) > deadzone) playerY += ly * speed;

            playerX = Clamp(playerX, 25, screenWidth - 25);
            playerY = Clamp(playerY, 25, screenHeight - 25);
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawCircle((int)playerX, (int)playerY, 25, BLUE);
            DrawCircleLines((int)playerX, (int)playerY, 25, DARKBLUE);

            DrawText("Use left analog stick to move the circle", 50, 10, 20, DARKGRAY);
            if (!IsGamepadAvailable(0)) {
                DrawText("No gamepad connected - connect one to use", 50, 50, 20, RED);
            }
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 27.1: Map both analog sticks to control a character.
// Left stick moves, right stick changes color (R: X axis, G: Y axis).
void challenge_dual_stick_control() {
    std::cout << "Challenge 27.1 incomplete - fill in the TODOs!\n";

    // TODO: Create a raylib window with dual-stick control
    // Left stick: move a square
    // Right stick: modulate color (X axis -> R, Y axis -> G, B stays 255)
    // Display both axis values on screen

    std::cout << "Hint: GetGamepadAxisMovement for both LEFT_X/LEFT_Y and RIGHT_X/RIGHT_Y\n";
}

void exercise_gamepad_input() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 27: Gamepad Input\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_gamepad_detection();
    std::cout << "Example 1 done.\n";
    example_joystick_movement();
    std::cout << "Example 2 done.\n";
    challenge_dual_stick_control();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 27 complete!\n";
    std::cout << "========================================\n";
}
