#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <cmath>

// ============================================================
// EXERCISE 46: Tilemaps
// ============================================================

// CONCEPT: tilemaps
// - Grid-based rendering using a 2D array
// - Each cell contains a tile type ID
// - Draw by iterating grid and rendering appropriate tile
// - Tile atlas: single texture with multiple tile images
// - Camera scrolling: offset rendering by camera position
// - Efficient: only draw tiles visible on screen

void example_tilemap_basic() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 46: Tilemap Basics");

    const int cols = 20;
    const int rows = 15;
    const int tileSize = 64;

    int map[rows][cols];
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            if (y == 0 || y == rows - 1 || x == 0 || x == cols - 1)
                map[y][x] = 1;
            else if (y > 5 && y < 10 && x > 5 && x < 10)
                map[y][x] = 2;
            else
                map[y][x] = 0;
        }
    }

    Image grassImg = GenImageColor(tileSize, tileSize, GREEN);
    Image wallImg = GenImageColor(tileSize, tileSize, DARKGRAY);
    Image waterImg = GenImageColor(tileSize, tileSize, BLUE);

    Texture2D grassTex = LoadTextureFromImage(grassImg);
    Texture2D wallTex = LoadTextureFromImage(wallImg);
    Texture2D waterTex = LoadTextureFromImage(waterImg);

    UnloadImage(grassImg);
    UnloadImage(wallImg);
    UnloadImage(waterImg);

    Texture2D tiles[] = {grassTex, wallTex, waterTex};
    Color colors[] = {GREEN, DARKGRAY, BLUE};

    Vector2 cameraOffset = {0, 0};
    float speed = 200.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_RIGHT)) cameraOffset.x -= speed * GetFrameTime();
        if (IsKeyDown(KEY_LEFT)) cameraOffset.x += speed * GetFrameTime();
        if (IsKeyDown(KEY_DOWN)) cameraOffset.y -= speed * GetFrameTime();
        if (IsKeyDown(KEY_UP)) cameraOffset.y += speed * GetFrameTime();

        cameraOffset.x = Clamp(cameraOffset.x, -(float)(cols * tileSize - screenWidth), 0);
        cameraOffset.y = Clamp(cameraOffset.y, -(float)(rows * tileSize - screenHeight), 0);

        BeginDrawing();
            ClearBackground(BLACK);

            int startX = (int)(-cameraOffset.x / tileSize);
            int startY = (int)(-cameraOffset.y / tileSize);
            int endX = startX + screenWidth / tileSize + 2;
            int endY = startY + screenHeight / tileSize + 2;

            for (int y = startY; y < endY && y < rows; y++) {
                for (int x = startX; x < endX && x < cols; x++) {
                    if (y < 0 || x < 0) continue;
                    int tile = map[y][x];
                    DrawTextureV(tiles[tile], (Vector2){
                        x * tileSize + cameraOffset.x,
                        y * tileSize + cameraOffset.y
                    }, WHITE);

                    DrawRectangleLines(
                        (int)(x * tileSize + cameraOffset.x),
                        (int)(y * tileSize + cameraOffset.y),
                        tileSize, tileSize, Fade(colors[tile], 0.3f));
                }
            }

            DrawRectangle(10, 10, 180, 80, Fade(RAYWHITE, 0.8f));
            DrawText("ARROWS: scroll map", 15, 15, 15, DARKGRAY);
            DrawText(TextFormat("View: (%d,%d)", startX, startY), 15, 35, 15, DARKGRAY);
            DrawText(TextFormat("Offset: (%.0f,%.0f)", cameraOffset.x, cameraOffset.y), 15, 55, 15, DARKGRAY);
            DrawFPS(700, 10);

        EndDrawing();
    }

    UnloadTexture(grassTex);
    UnloadTexture(wallTex);
    UnloadTexture(waterTex);
    CloseWindow();
}

// CHALLENGE 46.1: Create a tilemap with a player that walks on it.
// Use WASD to move, collision with wall tiles (type 1),
// different tile types for grass, water, walls, and goal.
void challenge_2d_rpg_tiles() {
    std::cout << "Challenge 46.1 incomplete - fill in the TODOs!\n";

    // TODO: Grid with 4+ tile types (0:grass, 1:wall, 2:water, 3:goal)
    // Player position in tile coordinates
    // WASD to move (check wall collision before moving)
    // Camera follows player
    // Display player on top of tiles

    std::cout << "Hint: Check map[playerY+dy][playerX+dx] != 1 before moving\n";
}

// CHALLENGE 46.2: Implement procedural tilemap generation using
// a simple random placement or cellular automata algorithm.
void challenge_procedural_generation() {
    std::cout << "Challenge 46.2 incomplete - fill in the TODOs!\n";

    // TODO: Initialize map with random walls (30% chance)
    // Or implement simple cellular automata cave generation:
    //   if neighbor walls >= 4: become wall, else: become floor
    // Display the generated map

    std::cout << "Hint: Use GetRandomValue(0, 99) < 30 for 30% wall probability\n";
}

void exercise_tilemaps() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 46: Tilemaps\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_tilemap_basic();
    std::cout << "Example done.\n";
    challenge_2d_rpg_tiles();
    challenge_procedural_generation();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 46 complete!\n";
    std::cout << "========================================\n";
}
