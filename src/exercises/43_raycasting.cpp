#include <raylib.h>
#include <iostream>
#include <vector>

// ============================================================
// EXERCISE 43: Raycasting
// ============================================================

// CONCEPT: raycasting in raylib
// - GetMouseRay(mousePos, camera): get a Ray from camera through mouse
// - GetRayCollisionSphere(ray, center, radius): ray vs sphere
// - GetRayCollisionBox(ray, box): ray vs bounding box
// - GetRayCollisionMesh(ray, mesh, transform): ray vs mesh
// - GetRayCollisionTriangle(ray, v1, v2, v3): ray vs triangle
// - Ray struct: .position, .direction
// - RayCollision struct: .hit, .distance, .point, .normal

void example_mouse_picking() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 43: Mouse Picking");

    Camera3D camera = {0};
    camera.position = (Vector3){8.0f, 6.0f, 8.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);

    struct PickableObject {
        Vector3 position;
        float radius;
        Color color;
        bool selected;
    };

    PickableObject objects[] = {
        {{-3, 1, -3}, 0.5f, RED, false},
        {{0, 1, -3}, 0.8f, GREEN, false},
        {{3, 1, -3}, 0.6f, BLUE, false},
        {{-3, 0.5f, 3}, 0.7f, PURPLE, false},
        {{3, 1.5f, 3}, 0.5f, ORANGE, false},
        {{0, 1, 3}, 0.9f, YELLOW, false},
    };
    int numObjects = 6;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        Ray ray = GetMouseRay(GetMousePosition(), camera);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < numObjects; i++) {
                RayCollision collision = GetRayCollisionSphere(ray, objects[i].position, objects[i].radius);
                objects[i].selected = collision.hit;
            }
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);

                for (int i = 0; i < numObjects; i++) {
                    Color c = objects[i].selected ? LIME : objects[i].color;
                    DrawSphere(objects[i].position, objects[i].radius, c);
                    DrawSphereWires(objects[i].position, objects[i].radius, 16, 16, objects[i].selected ? GREEN : DARKGRAY);
                }

                RayCollision mouseOver;
                bool hovering = false;
                for (int i = 0; i < numObjects; i++) {
                    mouseOver = GetRayCollisionSphere(ray, objects[i].position, objects[i].radius);
                    if (mouseOver.hit) {
                        hovering = true;
                        break;
                    }
                }

                if (hovering) {
                    DrawLine3D(ray.position, mouseOver.point, YELLOW);
                }
            EndMode3D();

            int selectedCount = 0;
            for (int i = 0; i < numObjects; i++) {
                if (objects[i].selected) selectedCount++;
            }

            DrawText("LEFT CLICK: select objects  (Hover to highlight)", 50, 10, 20, DARKGRAY);
            DrawText(TextFormat("Selected: %d objects", selectedCount), 50, 400, 20, DARKGRAY);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 43.1: Create a 3D shooting gallery with targets.
// Click on spheres to "shoot" them - they change color and disappear.
// Count score and show remaining targets.
void challenge_shooting_gallery() {
    std::cout << "Challenge 43.1 incomplete - fill in the TODOs!\n";

    // TODO: 10 spheres scattered in 3D space
    // GetMouseRay on click, CheckCollisionRaySphere
    // Hit target: mark as "dead" (don't draw, increment score)
    // Display score, remaining targets

    std::cout << "Hint: Use GetRayCollisionSphere for each target on click\n";
}

// CHALLENGE 43.2: Implement a 3D box picker.
// Draw 5 cubes, use GetRayCollisionBox to detect which cube is clicked.
// Highlight the selected cube with a wireframe.
void challenge_box_picking() {
    std::cout << "Challenge 43.2 incomplete - fill in the TODOs!\n";

    // TODO: Place cubes at different positions
    // For each: create BoundingBox {pos - size/2, pos + size/2}
    // GetRayCollisionBox on click

    std::cout << "Hint: BoundingBox box = { {x-1, y-1, z-1}, {x+1, y+1, z+1} }\n";
}

void exercise_raycasting() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 43: Raycasting\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_mouse_picking();
    std::cout << "Example done.\n";
    challenge_shooting_gallery();
    challenge_box_picking();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 43 complete!\n";
    std::cout << "========================================\n";
}
