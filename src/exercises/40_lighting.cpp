#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 40: Lighting
// ============================================================

// CONCEPT: basic lighting in raylib
// - raylib doesn't have built-in lighting - uses shaders
// - rlgl.h provides basic lighting setup functions
// - We simulate lighting with color manipulation for learning
// - Simple approach: compute face brightness based on light direction
// - For real lighting: use shaders (exercise 41)

void example_simulated_lighting() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 40: Simulated Lighting");

    Camera3D camera = {0};
    camera.position = (Vector3){8.0f, 6.0f, 8.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        float time = GetTime();

        Vector3 lightDir = {
            sin(time * 0.5f),
            cos(time * 0.3f) * 0.5f + 0.5f,
            cos(time * 0.5f)
        };
        float len = sqrt(lightDir.x * lightDir.x + lightDir.y * lightDir.y + lightDir.z * lightDir.z);
        lightDir.x /= len; lightDir.y /= len; lightDir.z /= len;

        Vector3 cubePositions[] = {{-3, 1, -3}, {3, 1, -3}, {-3, 1, 3}, {3, 1, 3}, {0, 1, 0}};
        int colorBases[] = {255, 200, 150, 100, 50};

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                DrawSphere((Vector3){lightDir.x * 5, lightDir.y * 5 + 2.5f, lightDir.z * 5}, 0.3f, YELLOW);

                for (int i = 0; i < 5; i++) {
                    Vector3 toLight = {
                        lightDir.x - cubePositions[i].x,
                        lightDir.y - cubePositions[i].y,
                        lightDir.z - cubePositions[i].z
                    };
                    float brightness = Clamp((toLight.x * lightDir.x + toLight.y * lightDir.y + toLight.z * lightDir.z) * 0.5f + 0.5f, 0.2f, 1.0f);
                    unsigned char c = (unsigned char)(colorBases[i] * brightness);
                    DrawCube(cubePositions[i], 1.5f, 1.5f, 1.5f, (Color){c, (unsigned char)(c * 0.8f), (unsigned char)(c * 0.2f), 255});
                }

                DrawText("Light source", 50, 340, 20, DARKGRAY);
            EndMode3D();

            DrawText("Simulated Lighting (no shaders required)", 50, 10, 20, DARKGRAY);
            DrawText(TextFormat("Light: (%.2f, %.2f, %.2f)", lightDir.x, lightDir.y, lightDir.z), 50, 400, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 40.1: Create colored lighting - 3 light sources (red, green, blue)
// at different positions. Compute the combined lighting on objects.
void challenge_colored_lights() {
    std::cout << "Challenge 40.1 incomplete - fill in the TODOs!\n";

    // TODO: 3 light positions orbiting at different angles
    // For each cube, compute the brightness from each light
    // Combine: finalColor = color * (r_light * r_brightness + g_light * g_brightness + ...)
    // Clamp values to valid range

    std::cout << "Hint: Combine red/green/blue contributions for each cube\n";
}

// CHALLENGE 40.2: Implement a basic flashlight that follows the camera.
// Objects in front of the camera appear brighter.
void challenge_flashlight() {
    std::cout << "Challenge 40.2 incomplete - fill in the TODOs!\n";

    // TODO: Camera3D in FREE mode
    // Use camera.position and camera.target to compute direction
    // Compute dot product of (object - camera) direction with camera forward
    // Objects facing the camera forward direction get brighter

    std::cout << "Hint: Flashlight direction = normalize(camera.target - camera.position)\n";
}

void exercise_lighting() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 40: Lighting\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_simulated_lighting();
    std::cout << "Example done.\n";
    challenge_colored_lights();
    challenge_flashlight();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 40 complete!\n";
    std::cout << "========================================\n";
}
