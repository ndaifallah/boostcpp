#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 37: 3D Shapes
// ============================================================

// CONCEPT: 3D shapes in raylib
// - DrawCube(center, w, h, d, color)
// - DrawCubeWires(center, w, h, d, color)
// - DrawSphere(center, radius, color)
// - DrawSphereWires(center, radius, rings, slices, color)
// - DrawCylinder(center, radiusTop, radiusBottom, height, slices, color)
// - DrawCylinderWires(center, radiusTop, radiusBottom, height, slices, color)
// - DrawCapsule(startPos, endPos, radius, slices, rings, color)

void example_3d_shapes_overview() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 37: 3D Shapes");

    Camera3D camera = {0};
    camera.position = (Vector3){12.0f, 8.0f, 12.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                DrawCube((Vector3){-5, 1, -5}, 2, 2, 2, RED);
                DrawCubeWires((Vector3){-5, 1, -5}, 2, 2, 2, MAROON);

                DrawSphere((Vector3){5, 1, -5}, 1.5f, BLUE);
                DrawSphereWires((Vector3){5, 1, -5}, 1.5f, 16, 16, DARKBLUE);

                DrawCylinder((Vector3){-5, 1, 5}, 1.0f, 1.0f, 2.0f, 16, GREEN);
                DrawCylinderWires((Vector3){-5, 1, 5}, 1.0f, 1.0f, 2.0f, 16, DARKGREEN);

                DrawCylinder((Vector3){5, 1, 5}, 0.5f, 1.5f, 2.0f, 16, PURPLE);
                DrawCylinderWires((Vector3){5, 1, 5}, 0.5f, 1.5f, 2.0f, 16, DARKPURPLE);
            EndMode3D();

            DrawText("3D Shapes Overview", 50, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 37.1: Draw a 3D scene with a table (box), a sphere on top,
// and a torus floating above. Use different colors and wireframe overlays.
void challenge_3d_composition() {
    std::cout << "Challenge 37.1 incomplete - fill in the TODOs!\n";

    // TODO: Create a Camera3D (orbital), draw:
    //   - Table: DrawCube as a flat wide box
    //   - Ball: DrawSphere on top of table
    //   - Torus: DrawTorus floating above (if available, or use rings)
    //   - DrawGrid for ground reference

    std::cout << "Hint: Table = {0, 0.5, 0} with size {4, 0.5, 2}, sphere at {0, 1.5, 0}\n";
}

// CHALLENGE 37.2: Create a rotating ring of spheres (like an atom model).
// 6 spheres orbiting a center sphere at different angles.
void challenge_atom_model() {
    std::cout << "Challenge 37.2 incomplete - fill in the TODOs!\n";

    // TODO: Camera3D orbital
    // DrawSphere at origin (nucleus)
    // For 3+ orbital rings:
    //   Different tilt angles, spheres at radius r from center
    //   Animate rotation over time
    // DrawSphereWires for orbit paths

    std::cout << "Hint: Use sin/cos with time-based angle, rotate around different axes\n";
}

void exercise_3d_shapes() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 37: 3D Shapes\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_3d_shapes_overview();
    std::cout << "Example done.\n";
    challenge_3d_composition();
    challenge_atom_model();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 37 complete!\n";
    std::cout << "========================================\n";
}
