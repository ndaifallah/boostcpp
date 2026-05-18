#include "61_scene_graph.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

// ============================================================
// EXERCISE 61: Scene Graph / Node Hierarchy
// ============================================================

// CONCEPT: hierarchical transformation graph
// - Each node has a local transform (position, rotation, scale)
// - Children inherit parent transforms
// - Used for complex animated objects (robots, skeletons, vehicles)
// - Transform tree: root >> child >> grandchild

struct SceneNode {
    Vector2 pos;
    float rot;
    Vector2 scale;
    Color color;
    std::vector<std::unique_ptr<SceneNode>> children;

    SceneNode(Vector2 p, float r, Vector2 s, Color c)
        : pos(p), rot(r), scale(s), color(c) {}

    void addChild(std::unique_ptr<SceneNode> child) {
        children.push_back(std::move(child));
    }

    Matrix getLocalMatrix() const {
        Matrix t = MatrixTranslate(pos.x, pos.y, 0);
        Matrix r = MatrixRotateZ(rot * DEG2RAD);
        Matrix s = MatrixScale(scale.x, scale.y, 1);
        return MatrixMultiply(MatrixMultiply(t, r), s);
    }

    void draw(Matrix parentTransform) const {
        Matrix local = getLocalMatrix();
        Matrix world = MatrixMultiply(local, parentTransform);

        // Extract position from world matrix for 2D drawing
        Vector3 worldPos = {world.m12, world.m13, world.m14};

        // Draw this node
        DrawCircleV({worldPos.x, worldPos.y}, 10, color);
        DrawCircleLines((int)worldPos.x, (int)worldPos.y, 10, WHITE);

        for (const auto &child : children) {
            child->draw(world);
        }
    }
};

void example_scene_graph() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 61: Scene Graph");

    // Build a robot arm hierarchy
    auto root = std::make_unique<SceneNode>(
        Vector2{400, 300}, 0, Vector2{1, 1}, WHITE);

    auto upperArm = std::make_unique<SceneNode>(
        Vector2{0, -40}, 0, Vector2{1, 1}, RED);
    auto upperArmPtr = upperArm.get();
    root->addChild(std::move(upperArm));

    auto forearm = std::make_unique<SceneNode>(
        Vector2{0, -40}, 0, Vector2{1, 1}, BLUE);
    auto forearmPtr = forearm.get();
    upperArmPtr->addChild(std::move(forearm));

    auto hand = std::make_unique<SceneNode>(
        Vector2{0, -30}, 0, Vector2{1, 1}, GREEN);
    auto handPtr = hand.get();
    forearmPtr->addChild(std::move(hand));

    // Add fingers to hand
    for (int i = -8; i <= 8; i += 8) {
        auto finger = std::make_unique<SceneNode>(
            Vector2{(float)i, -15}, 0, Vector2{1, 1}, YELLOW);
        handPtr->addChild(std::move(finger));
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float t = GetTime();

        // Animate the hierarchy
        root->rot = sinf(t * 0.3f) * 30;
        upperArmPtr->rot = sinf(t * 0.5f) * 45 + 20;
        forearmPtr->rot = sinf(t * 0.7f) * 60 - 30;
        handPtr->rot = sinf(t * 0.9f) * 20;

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Exercise 61: Scene Graph (Robot Arm)", 50, 30, 20, WHITE);
        DrawText("Each joint inherits parent's transform", 50, 55, 15, GRAY);

        Matrix identity = MatrixIdentity();
        root->draw(identity);

        // Draw connections between joints (visualize hierarchy)
        // Using the world positions recalculated
        Vector2 rp = root->pos;
        Matrix rMat = root->getLocalMatrix();
        Matrix uMat = MatrixMultiply(upperArmPtr->getLocalMatrix(), rMat);
        Matrix fMat = MatrixMultiply(forearmPtr->getLocalMatrix(), uMat);
        Matrix hMat = MatrixMultiply(handPtr->getLocalMatrix(), fMat);

        Vector3 up = {uMat.m12, uMat.m13, 0};
        Vector3 fp = {fMat.m12, fMat.m13, 0};
        Vector3 hp = {hMat.m12, hMat.m13, 0};

        DrawLineV({up.x, up.y}, {fp.x, fp.y}, DARKGRAY);
        DrawLineV({fp.x, fp.y}, {hp.x, hp.y}, DARKGRAY);

        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 61.1: Extend the scene graph to 3D.
// Each node has a 3D transform (Vector3 position, Vector3 rotation, Vector3 scale)
// and draws a 3D shape (cube, sphere, cylinder).
void challenge_3d_scene_graph() {
    std::cout << "Challenge 61.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct SceneNode3D { Vector3 pos; Vector3 rot; Vector3 scale; ... };
    //   Build a solar system: Sun > Earth > Moon
    //   Each orbits its parent using hierarchical transforms
    //   Draw as spheres with different colors
    //   Animate continuously

    std::cout << "Hint: Use MatrixMultiply for hierarchical 3D transforms\n";
}

// CHALLENGE 61.2: Add visibility and enable/disable toggles to nodes.
// Clicking a node toggles its visibility.
void challenge_node_toggles() {
    std::cout << "Challenge 61.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Add "bool visible" to SceneNode
    //   If !visible, skip drawing self and children
    //   Check mouse click against node circles
    //   Toggle visibility on click

    std::cout << "Hint: Use CheckCollisionPointCircle for mouse hit detection\n";
}

void exercise_scene_graph() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 61: Scene Graph / Node Hierarchy\n";
    std::cout << "========================================\n";
    std::cout << "Opening scene graph demo - close window to continue...\n\n";

    example_scene_graph();
    std::cout << "Scene graph demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_3d_scene_graph();
    challenge_node_toggles();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 61 complete!\n";
    std::cout << "========================================\n";
}
