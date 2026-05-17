#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 39: Materials & Textures
// ============================================================

// CONCEPT: materials in raylib
// - Material struct: shaders, maps (albedo, normals, metallic, roughness, AO, etc.)
// - model.materials[index] to access materials
// - SetMaterialTexture(material, mapType, texture): apply texture
// - MATERIAL_MAP_ALBEDO: base color texture
// - MATERIAL_MAP_NORMAL: normal map for 3D detail
// - MATERIAL_MAP_METALNESS: metallic map
// - MATERIAL_MAP_ROUGHNESS: roughness map
// - MATERIAL_MAP_OCCLUSION: ambient occlusion
// - MATERIAL_MAP_EMISSION: emissive map (glow)

void example_material_textures() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 39: Materials & Textures");

    Camera3D camera = {0};
    camera.position = (Vector3){8.0f, 6.0f, 8.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Image checkImg = GenImageChecked(256, 256, 32, 32, RED, WHITE);
    Texture2D checkTex = LoadTextureFromImage(checkImg);
    UnloadImage(checkImg);

    Image circleImg = GenImageColor(256, 256, BLANK);
    ImageDrawCircle(&circleImg, 128, 128, 100, BLUE);
    ImageDrawCircleLines(&circleImg, 128, 128, 100, DARKBLUE);
    Texture2D circleTex = LoadTextureFromImage(circleImg);
    UnloadImage(circleImg);

    Model sphere = LoadModelFromMesh(GenMeshSphere(1.5f, 32, 32));
    Model cube = LoadModelFromMesh(GenMeshCube(2, 2, 2));

    sphere.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = checkTex;
    cube.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = circleTex;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                DrawModel(sphere, (Vector3){-3, 1, 0}, 1.0f, WHITE);
                DrawModel(cube, (Vector3){3, 1, 0}, 1.0f, WHITE);
            EndMode3D();

            DrawText("Materials: Textured Models", 50, 10, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    UnloadModel(sphere);
    UnloadModel(cube);
    UnloadTexture(checkTex);
    UnloadTexture(circleTex);
    CloseWindow();
}

// CHALLENGE 39.1: Apply a generated texture to a cylinder and a torus.
// Show all 4 models (cube, sphere, cylinder, torus) with different generated textures.
void challenge_all_textured() {
    std::cout << "Challenge 39.1 incomplete - fill in the TODOs!\n";

    // TODO: Generate 4 different textures (e.g., stripes, dots, gradient, checker)
    // LoadModelFromMesh for cube, sphere, cylinder, torus
    // SetMaterialTexture(... MATERIAL_MAP_ALBEDO, ...) for each
    // Display them in a row with labels

    std::cout << "Hint: Use GenImageChecked, GenImageGradientRadial, GenImageCellular\n";
}

// CHALLENGE 39.2: Use color tinting on a textured model.
// Draw the same model 4 times with different tint colors.
void challenge_tinted_textures() {
    std::cout << "Challenge 39.2 incomplete - fill in the TODOs!\n";

    // TODO: Single model (cube) with a generated texture
    // DrawModel 4 times at different positions with different tints
    // Use WHITE, RED, BLUE, GREEN tints to show the effect

    std::cout << "Hint: DrawModel(model, position, scale, tint) where tint modifies colors\n";
}

void exercise_materials_textures() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 39: Materials & Textures\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_material_textures();
    std::cout << "Example done.\n";
    challenge_all_textured();
    challenge_tinted_textures();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 39 complete!\n";
    std::cout << "========================================\n";
}
