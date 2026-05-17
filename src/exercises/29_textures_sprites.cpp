#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 29: Textures & Sprites
// ============================================================

// CONCEPT: textures and sprites in raylib
// - LoadTexture(path): load from file (PNG, JPG, BMP, etc.)
// - LoadTextureFromImage(image): create texture from Image
// - DrawTexture(texture, x, y, tint): basic draw
// - DrawTextureEx(texture, position, rotation, scale, tint): with params
// - DrawTextureV(texture, position, tint): with Vector2 position
// - UnloadTexture(texture): free GPU memory
// - Texture2D struct: .id, .width, .height, .format

void example_generated_textures() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 29: Generated Textures");

    Image checkImg = GenImageChecked(64, 64, 8, 8, RED, WHITE);
    Texture2D checkTex = LoadTextureFromImage(checkImg);
    UnloadImage(checkImg);

    Image circleImg = GenImageColor(64, 64, BLANK);
    ImageDrawCircle(&circleImg, 32, 32, 30, BLUE);
    ImageDrawCircleLines(&circleImg, 32, 32, 30, DARKBLUE);
    Texture2D circleTex = LoadTextureFromImage(circleImg);
    UnloadImage(circleImg);

    Image gradImg = GenImageGradientRadial(64, 64, 0.5f, WHITE, DARKPURPLE);
    Texture2D gradTex = LoadTextureFromImage(gradImg);
    UnloadImage(gradImg);

    SetTargetFPS(60);

    float rotation = 0.0f;

    while (!WindowShouldClose()) {
        rotation += GetFrameTime() * 30.0f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(checkTex, 50, 50, WHITE);
            DrawTextureEx(checkTex, (Vector2){50, 200}, rotation, 2.0f, WHITE);

            DrawTexture(circleTex, 250, 50, WHITE);
            DrawTextureEx(circleTex, (Vector2){250, 200}, rotation, 2.0f, WHITE);

            DrawTexture(gradTex, 450, 50, WHITE);
            DrawTextureEx(gradTex, (Vector2){450, 200}, -rotation, 2.0f, WHITE);

            DrawTextureV(checkTex, (Vector2){650, 50}, Fade(RED, 0.5f));

            DrawText("Generated Textures", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(checkTex);
    UnloadTexture(circleTex);
    UnloadTexture(gradTex);
    CloseWindow();
}

void example_load_external() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 29: External Textures");

    Texture2D tex = LoadTexture("cat.png");
    bool loaded = tex.id > 0;

    SetTargetFPS(60);

    float x = 0;
    float speed = 100.0f;

    while (!WindowShouldClose()) {
        x += speed * GetFrameTime();
        if (x > screenWidth) x = -100;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (loaded) {
                float scale = 0.5f;
                DrawTextureEx(tex, (Vector2){x, 150}, 0, scale, WHITE);
                DrawText(TextFormat("Texture: %dx%d", tex.width, tex.height), 50, 50, 20, DARKGRAY);
            } else {
                DrawText("Place 'cat.png' in the working directory", 50, 50, 20, RED);
                DrawText("or use generated textures instead", 50, 80, 20, RED);

                DrawRectangle(150, 100, 64, 64, GRAY);
                DrawRectangleLines(150, 100, 64, 64, DARKGRAY);
                DrawText("?", 174, 124, 30, DARKGRAY);
            }

            DrawText("Press ESC to exit", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    if (loaded) UnloadTexture(tex);
    CloseWindow();
}

// CHALLENGE 29.1: Create a texture from an image generated at runtime,
// then make a sprite follow the mouse position. Draw the sprite
// centered on the cursor.
void challenge_sprite_follow_mouse() {
    std::cout << "Challenge 29.1 incomplete - fill in the TODOs!\n";

    // TODO: Generate a texture at runtime (e.g., a colored circle or star)
    //   Image img = GenImageColor(64, 64, BLANK);
    //   ImageDrawCircle(&img, 32, 32, 28, ORANGE);
    //   Texture2D tex = LoadTextureFromImage(img);
    //   UnloadImage(img);

    // Inside game loop:
    //   ClearBackground(RAYWHITE)
    //   DrawTextureEx(tex, mousePos - {32, 32}, 0, 1.0f, WHITE)
    //   OR: DrawTextureV(tex, {mouse.x - 32, mouse.y - 32}, WHITE)
    //   Draw instructions

    // TODO: CloseWindow + UnloadTexture

    std::cout << "Hint: Use GetMousePosition(), then offset by half tex dimensions\n";
}

// CHALLENGE 29.2: Create a simple animation by swapping between 2-3
// generated textures at a fixed interval (frame timer).
void challenge_texture_animation() {
    std::cout << "Challenge 29.2 incomplete - fill in the TODOs!\n";

    // TODO: Generate 3 textures of a circle at different sizes (or different colors)
    // Store them in an array Texture2D frames[3]
    // int currentFrame = 0
    // float timer = 0
    // float frameDuration = 0.2f

    // Inside game loop:
    //   timer += GetFrameTime()
    //   if timer >= frameDuration: currentFrame = (currentFrame + 1) % 3, timer = 0
    //   DrawTextureEx(frames[currentFrame], position, 0, 2.0f, WHITE)

    // TODO: CloseWindow + UnloadTexture each frame

    std::cout << "Hint: Use GenImageColor + ImageDrawCircle for each frame\n";
}

void exercise_textures_sprites() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 29: Textures & Sprites\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_generated_textures();
    std::cout << "Example 1 done.\n";
    example_load_external();
    std::cout << "Example 2 done.\n";
    challenge_sprite_follow_mouse();
    challenge_texture_animation();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 29 complete!\n";
    std::cout << "========================================\n";
}
