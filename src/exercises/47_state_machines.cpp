#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// ============================================================
// EXERCISE 47: State Machines
// ============================================================

// CONCEPT: finite state machines for game states
// - Game states: MENU, PLAYING, PAUSED, GAME_OVER
// - Each state has independent logic and rendering
// - Transitions between states are triggered by events
// - State stack for pause overlays (push/pop)
// - Clean separation of concerns

enum GameState { MENU, PLAYING, PAUSED, GAME_OVER };

struct GameStateMachine {
    GameState currentState;
    GameState previousState;
};

void game_menu_update(GameStateMachine& gsm) {
    if (IsKeyPressed(KEY_SPACE)) {
        gsm.currentState = PLAYING;
    }
    if (IsKeyPressed(KEY_Q)) {
        CloseWindow();
    }
}

void game_playing_update(GameStateMachine& gsm, float& score, float& timer) {
    timer += GetFrameTime();
    const char* text = "Press SPACE when timer hits an exact second!";
    (void)text;

    if (IsKeyPressed(KEY_SPACE)) {
        float diff = fabs(fmod(timer, 1.0f) - 0.0f);
        if (diff < 0.1f) {
            score += 10;
        } else if (diff < 0.3f) {
            score += 5;
        } else {
            score += 1;
        }
    }

    if (IsKeyPressed(KEY_P)) {
        gsm.previousState = gsm.currentState;
        gsm.currentState = PAUSED;
    }

    if (timer > 30.0f) {
        gsm.currentState = GAME_OVER;
    }
}

void game_paused_update(GameStateMachine& gsm) {
    if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE)) {
        gsm.currentState = gsm.previousState;
    }
}

void example_state_machine() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 47: State Machine");

    GameStateMachine gsm = {MENU, MENU};
    float score = 0;
    float timer = 0;
    bool gameStarted = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        switch (gsm.currentState) {
            case MENU:
                game_menu_update(gsm);
                if (gsm.currentState == PLAYING && !gameStarted) {
                    score = 0;
                    timer = 0;
                    gameStarted = true;
                }
                break;
            case PLAYING:
                game_playing_update(gsm, score, timer);
                break;
            case PAUSED:
                game_paused_update(gsm);
                break;
            case GAME_OVER: {
                if (IsKeyPressed(KEY_SPACE)) {
                    gsm.currentState = MENU;
                    gameStarted = false;
                }
                break;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            switch (gsm.currentState) {
                case MENU:
                    DrawText("== TIMING GAME ==", 250, 100, 40, DARKBLUE);
                    DrawText("Press SPACE to start", 280, 200, 25, DARKGRAY);
                    DrawText("Press Q to quit", 320, 250, 20, DARKGRAY);
                    DrawText("Instructions:", 50, 350, 20, DARKGRAY);
                    DrawText("Press SPACE when the timer hits exact seconds!", 50, 380, 18, DARKGRAY);
                    DrawText("(closer = more points, P to pause)", 50, 410, 18, DARKGRAY);
                    break;

                case PLAYING:
                    DrawText("PLAYING", 50, 10, 30, GREEN);
                    DrawText(TextFormat("Score: %.0f", score), 50, 60, 25, DARKGRAY);
                    DrawText(TextFormat("Time: %.2f", timer), 50, 100, 25, DARKGRAY);
                    DrawText("Press P to pause", 600, 10, 20, DARKGRAY);

                    {
                        float progress = fmod(timer, 1.0f);
                        DrawRectangle(100, 200, 600, 40, LIGHTGRAY);
                        DrawRectangle(100, 200, (int)(600 * progress), 40, SKYBLUE);
                        DrawText("HIT!", 385, 200, 20, RED);
                    }
                    break;

                case PAUSED: {
                    DrawText("PLAYING", 50, 10, 30, GREEN);
                    DrawRectangle(0, 0, 800, 450, Fade(BLACK, 0.5f));
                    DrawText("== PAUSED ==", 300, 180, 40, WHITE);
                    DrawText(TextFormat("Score: %.0f", score), 360, 240, 25, WHITE);
                    DrawText("Press P or ESC to resume", 290, 300, 20, WHITE);
                    break;
                }

                case GAME_OVER:
                    DrawText("== GAME OVER ==", 260, 100, 40, MAROON);
                    DrawText(TextFormat("Final Score: %.0f", score), 300, 180, 30, DARKGRAY);
                    DrawText("Press SPACE to return to menu", 270, 280, 20, DARKGRAY);
                    break;
            }

            DrawFPS(700, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 47.1: Add a 4th state called "HIGH_SCORES" that shows
// saved scores and can be accessed from the MENU state.
void challenge_high_scores() {
    std::cout << "Challenge 47.1 incomplete - fill in the TODOs!\n";

    // TODO: Add HIGH_SCORES to GameState enum
    // Store top 5 scores in an array
    // KEY_H on menu goes to high scores
    // Display scores, KEY_B to go back

    std::cout << "Hint: std::vector<float> topScores, sort and keep top 5\n";
}

// CHALLENGE 47.2: Implement a state machine for a simple platformer
// with states: GROUNDED, JUMPING, FALLING, HURT.
// Transition: GROUNDED->JUMPING (on press), JUMPING->FALLING (apex),
// FALLING->GROUNDED (land), GROUNDED->HURT (hit enemy).
void challenge_platformer_states() {
    std::cout << "Challenge 47.2 incomplete - fill in the TODOs!\n";

    // TODO: enum PlayerState { GROUNDED, JUMPING, FALLING, HURT }
    // Switch on state for update logic
    // Display current state as text on screen
    // SPACE to jump from grounded, timer transitions JUMPING->FALLING
    // ENEMY collision from GROUNDED -> HURT

    std::cout << "Hint: jumpVelocity = -10, gravity = 30, when y >= ground: GROUNDED\n";
}

void exercise_state_machines() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 47: State Machines\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_state_machine();
    std::cout << "Example done.\n";
    challenge_high_scores();
    challenge_platformer_states();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 47 complete!\n";
    std::cout << "========================================\n";
}
