#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 23: Polygons & Triangles
// ============================================================

// CONCEPT: polygon drawing in raylib
// - DrawTriangle(v1, v2, v3, color): filled triangle
// - DrawTriangleLines(v1, v2, v3, color): triangle outline
// - DrawPoly(center, sides, radius, rotation, color): regular polygon
// - DrawPolyLines(center, sides, radius, rotation, color): polygon outline
// - DrawRectangleLinesEx(rect, thickness, color): bordered rectangle

void example_triangles() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 23: Triangles");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTriangle((Vector2){100, 50}, (Vector2){50, 200}, (Vector2){150, 200}, ORANGE);
            DrawTriangleLines((Vector2){200, 50}, (Vector2){250, 200}, (Vector2){150, 200}, BLUE);

            DrawTriangle((Vector2){400, 50}, (Vector2){350, 200}, (Vector2){450, 200}, GREEN);
            DrawTriangleLines((Vector2){400, 50}, (Vector2){450, 200}, (Vector2){350, 200}, RED);

            DrawText("Filled", 90, 210, 15, DARKGRAY);
            DrawText("Outline", 185, 210, 15, DARKGRAY);

            DrawFPS(10, 10);
            DrawText("Triangles - press ESC to exit", 280, 400, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void example_polygons() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 23: Polygons");

    SetTargetFPS(60);

    int sides = 3;
    float rotation = 0.0f;

    while (!WindowShouldClose()) {
        rotation += 0.5f;
        sides = 3 + (GetTime() / 2);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawPoly((Vector2){150, 200}, 3, 80, rotation, RED);
            DrawPoly((Vector2){300, 200}, 4, 80, rotation, GREEN);
            DrawPoly((Vector2){450, 200}, 5, 80, rotation, BLUE);
            DrawPoly((Vector2){600, 200}, 6, 80, rotation, PURPLE);
            DrawPoly((Vector2){750, 200}, 8, 80, rotation, ORANGE);

            DrawPolyLines((Vector2){150, 350}, 3, 60, rotation, RED);
            DrawPolyLines((Vector2){300, 350}, 4, 60, rotation, GREEN);
            DrawPolyLines((Vector2){450, 350}, 5, 60, rotation, BLUE);
            DrawPolyLines((Vector2){600, 350}, 6, 60, rotation, PURPLE);
            DrawPolyLines((Vector2){750, 350}, 8, 60, rotation, ORANGE);

            DrawText("3 sides", 132, 290, 15, DARKGRAY);
            DrawText("4 sides", 282, 290, 15, DARKGRAY);
            DrawText("5 sides", 432, 290, 15, DARKGRAY);
            DrawText("6 sides", 582, 290, 15, DARKGRAY);
            DrawText("8 sides", 730, 290, 15, DARKGRAY);

            DrawFPS(10, 10);
            DrawText("Polygons - press ESC to exit", 280, 420, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 23.1: Draw a hexagonal grid pattern filling the screen.
// Each hexagon should be bordered, and alternating rows should be offset.
void challenge_hexagonal_grid() {
    std::cout << "Challenge 23.1 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(800, 600, "Hexagonal Grid")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(DARKGRAY)
    //   Use DrawPoly to draw hexagons in a grid
    //   Hexagon: sides=6, rotation=30
    //   spacing = radius * 1.5 (horizontally), radius * sqrt(3) (vertically, or ~0.866)
    //   Offset every other row
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Use nested loops, offset every other column by radius*0.75\n";
}

// CHALLENGE 23.2: Draw a composition of triangles forming a geometric pattern (e.g., a diamond).
void challenge_geometric_composition() {
    std::cout << "Challenge 23.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 600, "Geometric Pattern")
    // TODO: SetTargetFPS(60)

    // Inside game loop:
    //   ClearBackground(RAYWHITE)
    //   Draw a diamond shape using 4 triangles (top, bottom, left, right)
    //   Use different colors for each triangle
    //   Draw a square outline around it
    //   DrawFPS

    // TODO: CloseWindow

    std::cout << "Hint: Center diamond at (300,300), use diagonal points\n";
}

void exercise_polygons_triangles() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 23: Polygons & Triangles\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_triangles();
    std::cout << "Example 1 done.\n";
    example_polygons();
    std::cout << "Example 2 done.\n";
    challenge_hexagonal_grid();
    challenge_geometric_composition();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 23 complete!\n";
    std::cout << "========================================\n";
}
