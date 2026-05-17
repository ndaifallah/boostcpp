#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 22: Lines & Curves
// ============================================================

// CONCEPT: lines and curves in raylib
// - DrawLine(x1, y1, x2, y2, color): basic line
// - DrawLineEx(start, end, thickness, color): thick line
// - DrawLineBezier(start, end, thickness, color): bezier curve
// - DrawSplineLinear(points, pointCount, thickness, color)
// - DrawSplineBasis(points, pointCount, thickness, color)
// - DrawSplineCatmullRom(points, pointCount, thickness, color)

void example_basic_lines() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 22: Basic Lines");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawLine(50, 50, 200, 50, RED);
            DrawLine(50, 100, 200, 150, GREEN);
            DrawLine(50, 200, 200, 100, BLUE);

            DrawLineEx((Vector2){300, 50}, (Vector2){500, 50}, 5, RED);
            DrawLineEx((Vector2){300, 100}, (Vector2){500, 200}, 8, GREEN);
            DrawLineEx((Vector2){300, 200}, (Vector2){500, 100}, 3, BLUE);

            DrawLineBezier((Vector2){600, 50}, (Vector2){750, 200}, 3, PURPLE);
            DrawLineBezier((Vector2){600, 100}, (Vector2){750, 300}, 5, ORANGE);

            DrawFPS(10, 10);
            DrawText("Lines and Bezier curves - press ESC to exit", 150, 400, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void example_curves_and_splines() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 22: Splines");

    SetTargetFPS(60);

    Vector2 points1[] = {
        {50, 200}, {200, 50}, {350, 300}, {500, 100}, {650, 350}
    };
    Vector2 points2[] = {
        {50, 400}, {200, 50}, {350, 350}, {500, 100}, {650, 400}
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawSplineLinear(points1, 5, 3, RED);
            DrawSplineBasis(points2, 5, 3, BLUE);

            for (int i = 0; i < 5; i++) {
                DrawCircle(points1[i].x, points1[i].y, 5, DARKGRAY);
                DrawCircle(points2[i].x, points2[i].y, 5, DARKGRAY);
            }

            DrawText("Linear spline (RED) and Basis spline (BLUE)", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 22.1: Draw a star pattern by connecting points on a circle with lines.
// Use sin/cos to compute point positions and DrawLine to connect them.
void challenge_star_pattern() {
    std::cout << "Challenge 22.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 600, "Star Pattern")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(BLACK)
    //   Compute 8 points on a circle (radius ~200, center ~300,300)
    //   Connect every point to every other point using DrawLine
    //   Use different colors (use a cycling color based on angle)
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Use sin() and cos() for point positions, loop through connections\n";
}

// CHALLENGE 22.2: Draw a parametric spiral curve using DrawCircle or small line segments.
void challenge_spiral() {
    std::cout << "Challenge 22.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 600, "Spiral")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(BLACK)
    //   Draw a spiral using small line segments
    //   Parametric: x = centerX + t*cos(t), y = centerY + t*sin(t)
    //   Use DrawLineEx between consecutive points
    //   DrawFPS with instructions

    // TODO: CloseWindow

    std::cout << "Hint: Use DrawLineEx between consecutive (t) and (t+dt) points\n";
}

void exercise_lines_curves() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 22: Lines & Curves\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_basic_lines();
    std::cout << "Example 1 done.\n";
    example_curves_and_splines();
    std::cout << "Example 2 done.\n";
    challenge_star_pattern();
    challenge_spiral();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 22 complete!\n";
    std::cout << "========================================\n";
}
