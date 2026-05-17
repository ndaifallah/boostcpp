#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 36: Camera 3D
// ============================================================

// CONCEPT: 3D camera in raylib
// - Camera3D struct: position, target, up, fovy, projection
// - CAMERA_ORBITAL: orbit around target (auto-rotates)
// - CAMERA_FIRST_PERSON: FPS-style controls (WASD + mouse)
// - CAMERA_FREE: fly around freely
// - CAMERA_THIRD_PERSON: behind a target
// - BeginMode3D(camera) / EndMode3D(): draw 3D objects
// - UpdateCamera(camera, mode): auto-update based on mode

void example_3d_basics() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 36: 3D Basics");

    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        if (IsKeyPressed(KEY_ONE)) { camera.projection = CAMERA_PERSPECTIVE; }
        if (IsKeyPressed(KEY_TWO)) { camera.projection = CAMERA_ORTHOGRAPHIC; }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawCube((Vector3){-3, 0, 0}, 2, 2, 2, RED);
                DrawCubeWires((Vector3){-3, 0, 0}, 2, 2, 2, MAROON);

                DrawSphere((Vector3){3, 0, 0}, 1.5f, BLUE);
                DrawSphereWires((Vector3){3, 0, 0}, 1.5f, 16, 16, DARKBLUE);

                DrawGrid(10, 1.0f);
            EndMode3D();

            DrawText("CAMERA ORBITAL - mouse drag to orbit", 50, 10, 20, DARKGRAY);
            DrawText("1: Perspective  2: Orthographic", 50, 40, 20, DARKGRAY);
            DrawText(TextFormat("Projection: %s", camera.projection == CAMERA_PERSPECTIVE ? "PERSPECTIVE" : "ORTHOGRAPHIC"), 50, 400, 20, DARKGRAY);
            DrawFPS(10, 70);

        EndDrawing();
    }

    CloseWindow();
}

void example_first_person() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 36: First Person");

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 10.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    Vector3 cubePositions[] = {
        {-5, 0, -5}, {5, 0, -5}, {-5, 0, 5}, {5, 0, 5},
        {0, 0, -8}, {0, 0, 8}, {-8, 0, 0}, {8, 0, 0}
    };

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();
            ClearBackground(SKYBLUE);

            BeginMode3D(camera);
                DrawGrid(20, 1.0f);

                for (int i = 0; i < 8; i++) {
                    DrawCube(cubePositions[i], 1, 1, 1, (Color){(unsigned char)(i * 32), 100, 255, 255});
                    DrawCubeWires(cubePositions[i], 1, 1, 1, DARKGRAY);
                }

                DrawCube((Vector3){0, 0.5f, 0}, 0.5f, 1, 0.5f, BROWN);
            EndMode3D();

            DrawText("WASD: move  MOUSE: look around  1:FP  2:Orbital", 50, 10, 20, DARKGRAY);
            DrawText(TextFormat("Pos: (%.1f, %.1f, %.1f)", camera.position.x, camera.position.y, camera.position.z), 50, 400, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 36.1: Create a 3D scene with multiple cubes, spheres, and a cylinder
// arranged in a circle. Use CAMERA_ORBITAL to rotate the view.
void challenge_3d_scene() {
    std::cout << "Challenge 36.1 incomplete - fill in the TODOs!\n";

    // TODO: Camera3D with orbital mode, draw a ring of shapes
    // DrawCube, DrawSphere, DrawCylinder arranged in a circle
    // Use sin/cos to position them around origin
    // DrawGrid for reference

    std::cout << "Hint: For N objects: angle = i * 2*PI / N, pos = {radius*cos(angle), 0, radius*sin(angle)}\n";
}

// CHALLENGE 36.2: Create a third-person camera that follows a cube
// moving in a figure-8 pattern.
void challenge_third_person() {
    std::cout << "Challenge 36.2 incomplete - fill in the TODOs!\n";

    // TODO: Camera3D with CAMERA_THIRD_PERSON mode
    // Move a player cube in a figure-8 path
    //   x = sin(t) * 5, z = sin(t * 0.5f) * 5
    // Camera follows from behind

    std::cout << "Hint: camera.target = playerPos, camera.position = playerPos + offset\n";
}

void exercise_camera_3d() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 36: Camera 3D\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_3d_basics();
    std::cout << "Example 1 done.\n";
    example_first_person();
    std::cout << "Example 2 done.\n";
    challenge_3d_scene();
    challenge_third_person();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 36 complete!\n";
    std::cout << "========================================\n";
}
