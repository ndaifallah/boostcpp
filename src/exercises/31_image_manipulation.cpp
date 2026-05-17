#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 31: Image Manipulation
// ============================================================

// CONCEPT: image manipulation in raylib
// - LoadImage(path): load image into CPU memory
// - GenImageColor(width, height, color): generate
// - ImageResize(image, newW, newH): resize
// - ImageCrop(image, rect): crop
// - ImageFlipHorizontal(image), ImageFlipVertical(image)
// - ImageColorGrayscale(image): remove color
// - ImageColorInvert(image): invert colors
// - ImageDrawCircle, ImageDrawRectangle: draw on images
// - ExportImage(image, path): save to file
// - LoadTextureFromImage(image): convert to GPU texture

void example_image_effects() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 31: Image Effects");

    Image original = GenImageChecked(128, 128, 16, 16, RED, WHITE);
    Image copy1 = ImageCopy(original);
    Image copy2 = ImageCopy(original);
    Image copy3 = ImageCopy(original);

    ImageResize(&copy1, 64, 64);
    ImageResize(&copy2, 32, 32);

    ImageColorGrayscale(&copy3);
    ImageColorTint(&copy3, GREEN);
    ImageFlipVertical(&copy3);

    Texture2D tex0 = LoadTextureFromImage(original);
    Texture2D tex1 = LoadTextureFromImage(copy1);
    Texture2D tex2 = LoadTextureFromImage(copy2);
    Texture2D tex3 = LoadTextureFromImage(copy3);

    UnloadImage(original);
    UnloadImage(copy1);
    UnloadImage(copy2);
    UnloadImage(copy3);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(tex0, 50, 50, WHITE);
            DrawText("Original", 50, 190, 15, DARKGRAY);
            DrawTexture(tex1, 250, 50, WHITE);
            DrawText("Resized 64x64", 245, 190, 15, DARKGRAY);
            DrawTexture(tex2, 400, 50, WHITE);
            DrawText("Resized 32x32", 395, 190, 15, DARKGRAY);
            DrawTexture(tex3, 550, 50, WHITE);
            DrawText("Grayscale+Tint+Flip", 535, 190, 15, DARKGRAY);

            DrawText("Image Manipulation", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(tex0);
    UnloadTexture(tex1);
    UnloadTexture(tex2);
    UnloadTexture(tex3);
    CloseWindow();
}

void example_drawing_on_images() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 31: Drawing on Images");

    Image canvas = GenImageColor(400, 300, RAYWHITE);
    ImageDrawRectangle(&canvas, 50, 50, 100, 80, RED);
    ImageDrawCircle(&canvas, 250, 150, 60, BLUE);
    ImageDrawRectangleLines(&canvas, (Rectangle){300, 50, 80, 200}, 4, GREEN);
    ImageDrawText(&canvas, "Hello Image!", 100, 220, 20, DARKGRAY);

    Texture2D tex = LoadTextureFromImage(canvas);
    UnloadImage(canvas);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawTexture(tex, 200, 75, WHITE);
            DrawText("Drawing on CPU-side images", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadTexture(tex);
    CloseWindow();
}

// CHALLENGE 31.1: Load an image, convert it to grayscale, resize it to half,
// and display both original and processed versions side by side.
void challenge_image_processing() {
    std::cout << "Challenge 31.1 incomplete - fill in the TODOs!\n";

    // TODO: Generate a colorful image (or try to load from file)
    // Make a copy, apply grayscale, resize to half, flip horizontally
    // Load both as textures and display side by side

    std::cout << "Hint: Use ImageCopy, ImageColorGrayscale, ImageResize, ImageFlipHorizontal\n";
}

// CHALLENGE 31.2: Create a simple image editor: display an image,
// let the user draw on it with the mouse (hold left button to paint).
void challenge_paint_on_image() {
    std::cout << "Challenge 31.2 incomplete - fill in the TODOs!\n";

    // TODO: InitWindow(600, 450, "Paint on Image")
    // Image canvas = GenImageColor(600, 400, WHITE)
    // Texture2D tex = LoadTextureFromImage(canvas)
    // (Need to UpdateTexture after each modification)

    // Inside game loop:
    //   If IsMouseButtonDown(LEFT):
    //     Vector2 mouse = GetMousePosition()
    //     ImageDrawCircle(&canvas, mouse.x, mouse.y, 5, BLUE)
    //     UpdateTexture(tex, canvas.data)
    //   DrawTexture(tex, 0, 0, WHITE)

    // TODO: Cleanup

    std::cout << "Hint: UpdateTexture() re-uploads modified image data to GPU\n";
}

void exercise_image_manipulation() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 31: Image Manipulation\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_image_effects();
    std::cout << "Example 1 done.\n";
    example_drawing_on_images();
    std::cout << "Example 2 done.\n";
    challenge_image_processing();
    challenge_paint_on_image();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 31 complete!\n";
    std::cout << "========================================\n";
}
