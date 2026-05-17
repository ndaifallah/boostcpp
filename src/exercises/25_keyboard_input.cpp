#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <string>

// ============================================================
// EXERCISE 25: Keyboard Input
// ============================================================

// CONCEPT: keyboard input in raylib
// - IsKeyDown(key): true while key is held
// - IsKeyPressed(key): true once on press
// - IsKeyReleased(key): true once on release
// - IsKeyUp(key): true while not held
// - GetKeyPressed(): returns last pressed key (int)
// - SetExitKey(key): change the close-key shortcut

void example_keyboard_movement() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 25: Keyboard Movement");

    Rectangle player = {400, 200, 50, 50};
    float speed = 5.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player.x += speed;
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player.x -= speed;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player.y += speed;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) player.y -= speed;

        player.x = Clamp(player.x, 0, screenWidth - player.width);
        player.y = Clamp(player.y, 0, screenHeight - player.height);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawRectangleRec(player, BLUE);
            DrawRectangleLinesEx(player, 2, DARKBLUE);

            DrawText("Use ARROW KEYS or WASD to move the square", 50, 10, 20, DARKGRAY);
            DrawText(TextFormat("Position: (%.0f, %.0f)", player.x, player.y), 50, 400, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

void example_key_events() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 25: Key Events");

    SetTargetFPS(60);

    Color bgColor = RAYWHITE;
    int lastKey = 0;
    bool spaceHeld = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            bgColor = (bgColor.r == 255) ? LIGHTGRAY : RAYWHITE;
        }

        if (IsKeyPressed(KEY_R)) lastKey = KEY_R;
        else if (IsKeyPressed(KEY_G)) lastKey = KEY_G;
        else if (IsKeyPressed(KEY_B)) lastKey = KEY_B;
        else if (IsKeyReleased(KEY_SPACE)) lastKey = 0;

        int key = GetKeyPressed();
        if (key > 0) lastKey = key;

        spaceHeld = IsKeyDown(KEY_SPACE);

        BeginDrawing();
            ClearBackground(bgColor);

            DrawText("Press SPACE to toggle background", 50, 50, 20, DARKGRAY);
            DrawText("Press R, G, B to change text color hint", 50, 80, 20, DARKGRAY);
            DrawText("Press any key to see its code", 50, 110, 20, DARKGRAY);
            DrawText(TextFormat("Last key pressed: %d ('%c')", lastKey,
                (lastKey >= 32 && lastKey <= 126) ? lastKey : '?'), 50, 150, 25, DARKBLUE);
            DrawText(TextFormat("Space held: %s", spaceHeld ? "YES" : "no"), 50, 200, 20, DARKGRAY);

            DrawText("Press ESC to exit", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 25.1: Move a circle with WASD (8-directional: include diagonals).
// The circle should move faster in the diagonal direction (normalize).
void challenge_diagonal_movement() {
    std::cout << "Challenge 25.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 450, "Diagonal Movement")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   Vector2 position = {400, 225}
    //   float speed = 4.0f
    //   Check IsKeyDown for W, A, S, D
    //   Compute dx and dy (-1, 0, or 1 for each axis)
    //   Normalize diagonal: if dx != 0 && dy != 0, multiply by 0.7071
    //   Update position
    //   Clamp position to window bounds (with radius offset)
    //   ClearBackground, draw circle, draw instructions, draw FPS

    // TODO: CloseWindow

    std::cout << "Hint: Normalize by 0.7071 when moving diagonally (1/sqrt(2))\n";
}

// CHALLENGE 25.2: Implement a simple typing game - display a random letter
// and wait for the user to press it. Track accuracy and score.
void challenge_typing_game() {
    std::cout << "Challenge 25.2 incomplete - fill in the TODOs!\n";

    // TODO: Build a simple letter typing test in a raylib window
    // TODO: InitWindow(800, 300, "Typing Test")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   Display a random letter A-Z in large text
    //   Use GetKeyPressed() to get what the user typed
    //   Compare: correct increments score, wrong increments mistakes
    //   Show letter, score, mistakes
    //   Generate a new random letter after each attempt

    // TODO: CloseWindow

    std::cout << "Hint: Use GetRandomValue('A', 'Z') to get random char code\n";
}

void exercise_keyboard_input() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 25: Keyboard Input\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_keyboard_movement();
    std::cout << "Example 1 done.\n";
    example_key_events();
    std::cout << "Example 2 done.\n";
    challenge_diagonal_movement();
    challenge_typing_game();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 25 complete!\n";
    std::cout << "========================================\n";
}
