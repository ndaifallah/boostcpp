#include "62_save_load.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

// ============================================================
// EXERCISE 62: Save/Load System (serialization)
// ============================================================

// CONCEPT: persist game state to disk and restore it
// - Use raylib's LoadFileText / SaveFileText for convenience
// - Or standard C++ file I/O for more control
// - Serialize structured data (player, inventory, settings)
// - Load and reconstruct state on restart

struct PlayerData {
    Vector2 pos;
    int health;
    int score;
    std::string name;
};

struct GameState {
    PlayerData player;
    std::vector<Vector2> enemyPositions;
    float gameTime;
    int level;
};

std::string serializeGameState(const GameState &state) {
    std::ostringstream oss;
    oss << state.player.pos.x << " " << state.player.pos.y << "\n";
    oss << state.player.health << " " << state.player.score << "\n";
    oss << state.player.name << "\n";
    oss << state.enemyPositions.size() << "\n";
    for (const auto &ep : state.enemyPositions) {
        oss << ep.x << " " << ep.y << "\n";
    }
    oss << state.gameTime << " " << state.level << "\n";
    return oss.str();
}

bool deserializeGameState(const std::string &data, GameState &state) {
    std::istringstream iss(data);
    if (!(iss >> state.player.pos.x >> state.player.pos.y)) return false;
    if (!(iss >> state.player.health >> state.player.score)) return false;
    iss.ignore();
    if (!std::getline(iss, state.player.name)) return false;
    size_t enemyCount;
    if (!(iss >> enemyCount)) return false;
    state.enemyPositions.clear();
    for (size_t i = 0; i < enemyCount; i++) {
        Vector2 ep;
        if (!(iss >> ep.x >> ep.y)) return false;
        state.enemyPositions.push_back(ep);
    }
    if (!(iss >> state.gameTime >> state.level)) return false;
    return true;
}

void example_save_load() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 62: Save/Load System");

    GameState state;
    state.player.pos = {400, 300};
    state.player.health = 100;
    state.player.score = 0;
    state.player.name = "Hero";
    state.enemyPositions = {{100, 100}, {600, 100}, {350, 500}};
    state.gameTime = 0;
    state.level = 1;

    bool saved = false;
    bool loaded = false;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        state.gameTime += GetFrameTime();

        // Move player with arrow keys
        if (IsKeyDown(KEY_RIGHT)) state.player.pos.x += 3;
        if (IsKeyDown(KEY_LEFT)) state.player.pos.x -= 3;
        if (IsKeyDown(KEY_UP)) state.player.pos.y -= 3;
        if (IsKeyDown(KEY_DOWN)) state.player.pos.y += 3;

        state.player.pos.x = Clamp(state.player.pos.x, 20, screenWidth - 20);
        state.player.pos.y = Clamp(state.player.pos.y, 20, screenHeight - 20);

        // Save on S
        if (IsKeyPressed(KEY_S)) {
            std::string data = serializeGameState(state);
            bool success = SaveFileText("savegame.txt", data.data());
            saved = success;
            loaded = false;
        }

        // Load on L
        if (IsKeyPressed(KEY_L)) {
            char *data = LoadFileText("savegame.txt");
            if (data) {
                GameState loadedState;
                if (deserializeGameState(data, loadedState)) {
                    state = loadedState;
                    loaded = true;
                }
                UnloadFileText(data);
            }
            saved = false;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw enemies
        for (const auto &ep : state.enemyPositions) {
            DrawCircleV(ep, 15, RED);
            DrawCircleLines((int)ep.x, (int)ep.y, 15, MAROON);
        }

        // Draw player
        DrawCircleV(state.player.pos, 20, GREEN);
        DrawCircleLines((int)state.player.pos.x, (int)state.player.pos.y, 20, DARKGREEN);
        Vector2 tip = {state.player.pos.x, state.player.pos.y - 30};
        Vector2 left = {state.player.pos.x - 12, state.player.pos.y + 8};
        Vector2 right = {state.player.pos.x + 12, state.player.pos.y + 8};
        DrawTriangle(tip, left, right, DARKGREEN);

        // UI
        DrawText(TextFormat("Player: %s", state.player.name.c_str()), 50, 30, 20, WHITE);
        DrawText(TextFormat("Health: %d  Score: %d", state.player.health, state.player.score),
                 50, 55, 18, LIGHTGRAY);
        DrawText(TextFormat("Level: %d  Time: %.1f", state.level, state.gameTime),
                 50, 78, 16, GRAY);
        DrawText(TextFormat("Enemies: %zu", state.enemyPositions.size()), 50, 98, 16, GRAY);

        if (saved) DrawText("SAVED!", 350, 200, 30, GREEN);
        if (loaded) DrawText("LOADED!", 350, 200, 30, BLUE);

        DrawText("S: Save  L: Load  Arrows: Move", 50, screenHeight - 40, 15, GRAY);

        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 62.1: Add inventory serialization.
// Create an Item struct (name, quantity, type) and save/load a list of items.
void challenge_inventory_serialization() {
    std::cout << "Challenge 62.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   enum class ItemType { WEAPON, POTION, KEY, ARMOR };
    //   struct Item { std::string name; int quantity; ItemType type; };
    //   Add std::vector<Item> inventory to GameState
    //   Serialize: type name, quantity, type ID per line
    //   Show inventory on screen with I key

    std::cout << "Hint: Use a map or vector of Items, save count first then each item\n";
}

// CHALLENGE 62.2: Implement autosave every 10 seconds
// and slot-based save files (savegame_1.txt, savegame_2.txt, etc.).
void challenge_autosave_slots() {
    std::cout << "Challenge 62.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Use 3 save slots, select with keys 1/2/3
    //   Autosave to current slot every 10 seconds
    //   Display last save time for each slot
    //   Slot indicator on screen

    std::cout << "Hint: Store last save time, check (gameTime - lastSaveTime > 10)\n";
}

void exercise_save_load() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 62: Save/Load System\n";
    std::cout << "========================================\n";
    std::cout << "Opening save/load demo - close window to continue...\n\n";

    example_save_load();
    std::cout << "Save/load demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_inventory_serialization();
    challenge_autosave_slots();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 62 complete!\n";
    std::cout << "========================================\n";
}
