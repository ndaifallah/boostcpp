#include "63_multithreaded_loading.h"
#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <vector>

// ============================================================
// EXERCISE 63: Multi-Threaded Loading
// ============================================================

// CONCEPT: load assets in background threads while showing
// a loading screen. raylib rendering is single-threaded, but
// data preparation can happen off the main thread.
// - Use std::thread for background work
// - std::atomic for progress communication
// - Loading screen with progress bar
// - Simulated asset loading

struct GameAssets {
    Texture2D textures[4];
    bool loaded;
};

void loadAssetsAsync(GameAssets *assets, std::atomic<float> *progress) {
    *progress = 0.0f;

    // Simulate loading textures with procedural generation
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    *progress = 0.25f;
    Image img1 = GenImageGradientRadial(128, 128, 0.5f, RED, DARKBROWN);
    assets->textures[0] = LoadTextureFromImage(img1);
    UnloadImage(img1);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    *progress = 0.50f;
    Image img2 = GenImageGradientLinear(128, 128, 45, BLUE, DARKBLUE);
    assets->textures[1] = LoadTextureFromImage(img2);
    UnloadImage(img2);

    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    *progress = 0.75f;
    Image img3 = GenImageGradientSquare(128, 128, 0.6f, GREEN, DARKGREEN);
    assets->textures[2] = LoadTextureFromImage(img3);
    UnloadImage(img3);

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    *progress = 0.90f;
    Image img4 = GenImageGradientRadial(128, 128, 0.3f, PURPLE, MAROON);
    assets->textures[3] = LoadTextureFromImage(img4);
    UnloadImage(img4);

    assets->loaded = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    *progress = 1.0f;
}

void example_multithreaded_loading() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Exercise 63: Multi-Threaded Loading");

    GameAssets assets = {};
    assets.loaded = false;
    std::atomic<float> loadProgress{0.0f};
    std::thread loadThread;

    bool loading = true;
    bool showAssets = false;
    float rotation = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (loading && !loadThread.joinable()) {
            loadThread = std::thread(loadAssetsAsync, &assets, &loadProgress);
        }

        rotation += GetFrameTime() * 30;

        BeginDrawing();
        ClearBackground(BLACK);

        if (loading) {
            // Loading screen
            DrawText("Loading Assets...", 300, 200, 30, WHITE);

            // Progress bar background
            DrawRectangle(200, 280, 400, 30, DARKGRAY);
            DrawRectangleLines(200, 280, 400, 30, WHITE);

            // Progress bar fill
            DrawRectangle(200, 280, (int)(400 * loadProgress.load()), 30, GREEN);

            DrawText(TextFormat("%d%%", (int)(loadProgress.load() * 100)),
                     375, 315, 20, LIGHTGRAY);

            if (loadThread.joinable() && loadProgress.load() >= 1.0f) {
                loadThread.join();
                loading = false;
                showAssets = true;
            }

            DrawText("Assets load in background thread...", 280, 380, 15, GRAY);
        } else if (showAssets) {
            // Display loaded assets
            DrawText("Assets Loaded! (Press R to reload)", 250, 30, 20, WHITE);

            float spacing = 180;
            float startX = (screenWidth - spacing * 4) / 2 + spacing / 2;

            for (int i = 0; i < 4; i++) {
                float x = startX + i * spacing;
                float y = screenHeight / 2;

                DrawTexturePro(assets.textures[i],
                    {0, 0, (float)assets.textures[i].width, (float)assets.textures[i].height},
                    {x, y, 120, 120},
                    {60, 60},
                    rotation + i * 45,
                    WHITE);

                DrawRectangleLines((int)x - 60, (int)y - 60, 120, 120, WHITE);
                DrawText(TextFormat("Texture %d", i + 1), (int)x - 35, (int)y + 70, 15, GRAY);
            }

            DrawText("R: Reload  |  Assets loaded in background thread",
                     200, screenHeight - 40, 15, GRAY);

            if (IsKeyPressed(KEY_R)) {
                // Reset for reload
                for (auto &tex : assets.textures) {
                    if (tex.id > 0) UnloadTexture(tex);
                }
                assets.loaded = false;
                loadProgress.store(0.0f);
                loading = true;
                showAssets = false;
            }
        }

        DrawFPS(screenWidth - 100, 10);
        EndDrawing();
    }

    // Cleanup
    if (loadThread.joinable()) loadThread.join();
    for (auto &tex : assets.textures) {
        if (tex.id > 0) UnloadTexture(tex);
    }

    CloseWindow();
}

// CHALLENGE 63.1: Use std::async instead of std::thread for asset loading.
// Show how to get a return value (e.g., loading success/failure).
void challenge_async_loading() {
    std::cout << "Challenge 63.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   auto future = std::async(std::launch::async, loadAssetsAsync, ...);
    //   Check future status with future.wait_for(0ms)
    //   Get result with future.get() when done
    //   Display "Loading completed" vs "Loading failed"

    std::cout << "Hint: std::future_status::ready indicates completion\n";
}

// CHALLENGE 63.2: Implement a loading queue where multiple asset types
// (textures, sounds, meshes, fonts) are loaded in sequence on background threads.
void challenge_loading_queue() {
    std::cout << "Challenge 63.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct LoadTask { enum Type { TEXTURE, SOUND, MESH, FONT }; Type type; string path; };
    //   std::vector<LoadTask> queue = { ... };
    //   Process queue items one by one in a background thread
    //   Show detailed progress: "Loading texture 2/4...", "Loading sound 1/3..."
    //   When all done, switch to the main scene

    std::cout << "Hint: Use a vector of tasks and an atomic<int> for current task index\n";
}

void exercise_multithreaded_loading() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 63: Multi-Threaded Loading\n";
    std::cout << "========================================\n";
    std::cout << "Opening loading demo - close window to continue...\n\n";

    example_multithreaded_loading();
    std::cout << "Loading demo closed.\n";
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_async_loading();
    challenge_loading_queue();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 63 complete!\n";
    std::cout << "========================================\n";
}
