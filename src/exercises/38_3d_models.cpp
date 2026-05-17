#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 38: 3D Models
// ============================================================

// CONCEPT: 3D models in raylib
// - LoadModel(path): load OBJ/GLTF/glTF/VOX/M3D files
// - DrawModel(model, position, scale, tint): basic draw
// - DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint): with rotation
// - model.transform: Matrix for manual transforms
// - model.materials: array of Material for textures/colors
// - model.meshCount, model.meshes: mesh data
// - UnloadModel(model): cleanup
// - GenMeshCube/Sphere/... : generate procedural meshes

void example_procedural_models() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 38: Procedural Models");

    Camera3D camera = {0};
    camera.position = (Vector3){10.0f, 8.0f, 10.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model cubeModel = LoadModelFromMesh(GenMeshCube(2, 2, 2));
    Model sphereModel = LoadModelFromMesh(GenMeshSphere(1.5f, 16, 16));
    Model cylinderModel = LoadModelFromMesh(GenMeshCylinder(1.0f, 3.0f, 16));
    Model torusModel = LoadModelFromMesh(GenMeshTorus(0.8f, 1.5f, 16, 32));

    SetTargetFPS(60);

    float rotation = 0;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);
        rotation += GetFrameTime() * 30.0f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                DrawModel(cubeModel, (Vector3){-6, 1, -6}, 1.0f, RED);
                DrawModel(sphereModel, (Vector3){6, 1, -6}, 1.0f, BLUE);
                DrawModel(cylinderModel, (Vector3){-6, 1, 6}, 1.0f, GREEN);
                DrawModelEx(torusModel, (Vector3){6, 1, 6}, (Vector3){0, 1, 0}, rotation, (Vector3){1.0f, 1.0f, 1.0f}, PURPLE);
            EndMode3D();

            DrawText("Procedural Models (generated at runtime)", 50, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    UnloadModel(cubeModel);
    UnloadModel(sphereModel);
    UnloadModel(cylinderModel);
    UnloadModel(torusModel);
    CloseWindow();
}

// CHALLENGE 38.1: Create a model from GenMeshCube, rotate it around
// the Y-axis using DrawModelEx. Add a second smaller cube orbiting
// the first one (simulate a moon around a planet).
void challenge_orbit_models() {
    std::cout << "Challenge 38.1 incomplete - fill in the TODOs!\n";

    // TODO: LoadModelFromMesh(GenMeshCube(...)) for planet and moon
    // Inside game loop:
    //   DrawModelEx(planet, center, {0,1,0}, rotation, scale, color)
    //   DrawModelEx(moon, orbitPos, {0,1,0}, moonRotation, scale, color)
    //   orbitPos = center + {cos(angle)*radius, 0, sin(angle)*radius}

    std::cout << "Hint: Use DrawModelEx with rotationAxis {0,1,0} for Y-axis rotation\n";
}

// CHALLENGE 38.2: Create an animated character from combined meshes.
// Draw a head (sphere) + body (box) + arms (cylinders) using
// individual model draws with appropriate positions.
void challenge_combine_meshes() {
    std::cout << "Challenge 38.2 incomplete - fill in the TODOs!\n";

    // TODO: Create body: box, head: sphere, arms: cylinders
    // Position them relative to each other
    // Animate arms swinging (rotate around Z axis)

    std::cout << "Hint: body = {0,0,0}, head = {0,1.5,0}, left arm = {-1, 1, 0} etc.\n";
}

void exercise_3d_models() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 38: 3D Models\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_procedural_models();
    std::cout << "Example done.\n";
    challenge_orbit_models();
    challenge_combine_meshes();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 38 complete!\n";
    std::cout << "========================================\n";
}
