#include "57_3d_terrain.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <cmath>

// ============================================================
// EXERCISE 57: 3D Terrain (heightmap, perlin noise)
// ============================================================

// CONCEPT: generate and render 3D terrain
// - Use GenImageGradientRadial or raw pixel data for heightmaps
// - GenMeshHeightmap creates a 3D mesh from height data
// - Camera controls for terrain exploration
// - Texture mapping for visual variety

float perlinNoise1D(float x, float scale) {
    return sinf(x * scale) * 0.5f + sinf(x * scale * 2.1f) * 0.25f + sinf(x * scale * 3.7f) * 0.125f;
}

void example_terrain() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    const int mapSize = 256;
    const float terrainScale = 20.0f;
    const float heightScale = 5.0f;

    // Generate heightmap image
    Image heightmap = GenImageColor(mapSize, mapSize, BLACK);

    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            float nx = (float)x / mapSize;
            float ny = (float)y / mapSize;
            float h = perlinNoise1D(nx * 3.0f + ny * 2.0f, 2.5f)
                    + perlinNoise1D(nx * 5.0f - ny * 4.0f, 4.0f) * 0.5f
                    + perlinNoise1D(nx * 8.0f + ny * 7.0f, 6.0f) * 0.25f;
            h = (h + 1.0f) / 2.0f; // Normalize to [0, 1]
            unsigned char val = (unsigned char)(h * 255);
            ImageDrawPixel(&heightmap, x, y, {val, val, val, 255});
        }
    }

    Camera3D camera = {{0}};
    camera.position = {20, 15, 20};
    camera.target = {0, 0, 0};
    camera.up = {0, 1, 0};
    camera.fovy = 60;
    camera.projection = CAMERA_PERSPECTIVE;

    Mesh mesh = GenMeshHeightmap(heightmap, {mapSize * 0.2f, heightScale, mapSize * 0.2f});
    Model model = LoadModelFromMesh(mesh);

    // Create a simple terrain texture
    Image textureImg = GenImageColor(mapSize, mapSize, BLANK);
    for (int y = 0; y < mapSize; y++) {
        for (int x = 0; x < mapSize; x++) {
            unsigned char h = *((unsigned char *)heightmap.data + y * mapSize + x);
            Color c;
            if (h < 60) c = {30, 80, 180, 255};        // water
            else if (h < 100) c = {90, 180, 60, 255};   // grass
            else if (h < 170) c = {120, 100, 50, 255};  // dirt
            else c = {180, 180, 190, 255};               // snow
            ImageDrawPixel(&textureImg, x, y, c);
        }
    }
    Texture2D texture = LoadTextureFromImage(textureImg);
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    UnloadImage(heightmap);
    UnloadImage(textureImg);

    InitWindow(screenWidth, screenHeight, "Exercise 57: 3D Terrain");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(camera);
        DrawModel(model, (Vector3){-mapSize * 0.1f, -heightScale * 0.5f, -mapSize * 0.1f},
                  1.0f, WHITE);
        DrawGrid(20, 2.0f);
        EndMode3D();

        DrawText("Exercise 57: 3D Terrain (Heightmap)", 50, 20, 20, WHITE);
        DrawText("Orbital camera - drag to rotate", 50, 50, 15, GRAY);
        DrawFPS(screenWidth - 100, 10);

        EndDrawing();
    }

    UnloadTexture(texture);
    UnloadModel(model);
    CloseWindow();
}

// CHALLENGE 57.1: Add a small sphere that moves along the terrain surface.
// Sample the height at the sphere's (x,z) position and set its y accordingly.
void challenge_terrain_walker() {
    std::cout << "Challenge 57.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Draw a sphere that walks across the terrain
    //   Sample height using GetHeightValue (or re-calculate from noise)
    //   Use keyboard (WASD) to move the sphere
    //   The sphere should follow terrain height

    std::cout << "Hint: You can use GetRayCollisionMesh or recalculate noise height at position\n";
}

// CHALLENGE 57.2: Implement smooth first-person camera controls
// for walking across the terrain (WASD + mouse look).
void challenge_fps_camera() {
    std::cout << "Challenge 57.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Switch to CAMERA_FIRST_PERSON mode or manual camera
    //   WASD moves camera.position in look direction
    //   Mouse controls yaw and pitch
    //   Clamp camera y to terrain height + 2

    std::cout << "Hint: Use CAMERA_FIRST_PERSON or manually track yaw/pitch\n";
}

void exercise_3d_terrain() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 57: 3D Terrain (Heightmap)\n";
    std::cout << "========================================\n";
    std::cout << "Generating terrain - close window to continue...\n\n";

    example_terrain();
    std::cout << "Terrain demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_terrain_walker();
    challenge_fps_camera();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 57 complete!\n";
    std::cout << "========================================\n";
}
