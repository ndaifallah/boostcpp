#include "55_2d_animations.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 55: 2D Animations (tweening, easing)
// ============================================================

// CONCEPT: movement and animation using interpolation
// - Linear interpolation (lerp) between values
// - Easing functions for non-linear motion
// - Sequence-based animation with timing

float easeInOutQuad(float t) {
    return t < 0.5f ? 2.0f * t * t : 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
}

float easeOutBounce(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;
    if (t < 1.0f / d1) return n1 * t * t;
    float t2;
    if (t < 2.0f / d1) { t2 = t - 1.5f / d1; return n1 * t2 * t2 + 0.75f; }
    if (t < 2.5f / d1) { t2 = t - 2.25f / d1; return n1 * t2 * t2 + 0.9375f; }
    t2 = t - 2.625f / d1;
    return n1 * t2 * t2 + 0.984375f;
}

void example_tweening() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 55: 2D Animations & Tweening");

    Vector2 pos = {100, 300};
    float animTime = 0;
    float animDuration = 2.0f;
    int animIndex = 0;

    Color ballColors[] = {RED, GREEN, BLUE, YELLOW, PURPLE};
    const char *easingNames[] = {"Linear", "EaseInOutQuad", "EaseOutBounce", "Circular", "Elastic"};

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        animTime += dt;
        if (animTime > animDuration) {
            animTime -= animDuration;
            animIndex = (animIndex + 1) % 3;
        }

        float t = animTime / animDuration;

        // Different easing animations
        switch (animIndex) {
            case 0: // Linear
                pos.x = Lerp(100, 700, t);
                break;
            case 1: // EaseInOutQuad
                pos.x = Lerp(100, 700, easeInOutQuad(t));
                break;
            case 2: // Bounce
                pos.x = Lerp(100, 700, easeOutBounce(t));
                break;
        }

        BeginDrawing();
        ClearBackground(DARKGRAY);

        DrawCircleV(pos, 30, ballColors[animIndex]);
        DrawCircleLines((int)pos.x, (int)pos.y, 30, WHITE);

        DrawText(TextFormat("Easing: %s", easingNames[animIndex]), 50, 50, 25, WHITE);
        DrawText(TextFormat("Time: %.2f / %.2f", animTime, animDuration), 50, 80, 20, LIGHTGRAY);
        DrawText("Press SPACE to toggle easing function", 50, 520, 15, GRAY);

        if (IsKeyPressed(KEY_SPACE)) {
            animIndex = (animIndex + 1) % 3;
            animTime = 0;
        }

        // Draw path indicator
        DrawLine(100, 300, 700, 300, GRAY);
        for (int i = 0; i <= 10; i++) {
            float px = Lerp(100, 700, i / 10.0f);
            DrawCircleV({px, 320}, 3, LIGHTGRAY);
        }

        DrawFPS(700, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 55.1: Implement a sprite bouncing animation on the Y axis.
// Use easeOutBounce for the bounce, move from y=200 to y=500.
void challenge_bounce_animation() {
    std::cout << "Challenge 55.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Rectangle bounce from y=200 to y=500 using easeOutBounce
    //   Scale the rectangle horizontally when near ground (squash & stretch)
    //   Loop the animation continuously

    std::cout << "Hint: Use Lerp for position, scale x inversely to y compression\n";
}

// CHALLENGE 55.2: Create a color tweening animation.
// Smoothly transition from RED to BLUE to GREEN over 3 seconds.
void challenge_color_tween() {
    std::cout << "Challenge 55.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Color start = RED, mid = BLUE, end = GREEN
    //   Use t to interpolate between colors (lerp each channel)
    //   Draw a full-screen rectangle with the interpolated color
    //   Loop: 0->1 for RED->BLUE, 1->2 for BLUE->GREEN

    std::cout << "Hint: Color { (unsigned char)Lerp(r1,r2,t), ... }\n";
}

void exercise_2d_animations() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 55: 2D Animations & Tweening\n";
    std::cout << "========================================\n";
    std::cout << "Demonstrating easing functions - close window to continue...\n\n";

    example_tweening();
    std::cout << "Animation demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_bounce_animation();
    challenge_color_tween();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 55 complete!\n";
    std::cout << "========================================\n";
}
