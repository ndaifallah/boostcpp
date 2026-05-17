#include <raylib.h>
#include <iostream>

// ============================================================
// EXERCISE 41: Shaders Basics
// ============================================================

// CONCEPT: shaders in raylib
// - LoadShader(vertexPath, fragmentPath): load shader files
// - LoadShaderFromMemory(vertexCode, fragmentCode): from strings
// - GetShaderLocation(shader, name): get uniform location
// - SetShaderValue(shader, loc, value, type): set uniforms
// - BeginShaderMode(shader) / EndShaderMode(): apply to drawing
// - raylib includes default shaders: GetShaderDefault()
// - Shader struct: .id, .locs[]

// Default vertex shader is built-in, pass NULL to use it
// For simple post-processing effects, use fragment shaders

const char* grayscaleFragment = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;
void main() {
    vec4 texelColor = texture(texture0, fragTexCoord);
    float gray = dot(texelColor.rgb, vec3(0.299, 0.587, 0.114));
    finalColor = vec4(gray, gray, gray, texelColor.a) * colDiffuse;
}
)";

const char* invertFragment = R"(
#version 330
in vec2 fragTexCoord;
in vec4 fragColor;
uniform sampler2D texture0;
uniform vec4 colDiffuse;
out vec4 finalColor;
void main() {
    vec4 texelColor = texture(texture0, fragTexCoord);
    finalColor = vec4(1.0 - texelColor.rgb, texelColor.a) * colDiffuse;
}
)";

void example_post_processing() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Exercise 41: Post-Processing Shaders");

    Shader grayscale = LoadShaderFromMemory(NULL, grayscaleFragment);
    Shader invert = LoadShaderFromMemory(NULL, invertFragment);
    Shader currentShader = {0};

    int currentEffect = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_ONE)) { currentEffect = 0; currentShader = (Shader){0}; }
        if (IsKeyPressed(KEY_TWO)) { currentEffect = 1; currentShader = grayscale; }
        if (IsKeyPressed(KEY_THREE)) { currentEffect = 2; currentShader = invert; }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (currentShader.id > 0) BeginShaderMode(currentShader);

            DrawCircle(200, 200, 100, RED);
            DrawCircle(400, 200, 80, GREEN);
            DrawCircle(300, 150, 70, BLUE);
            DrawRectangle(500, 100, 150, 100, ORANGE);
            DrawTriangle((Vector2){550, 250}, (Vector2){650, 350}, (Vector2){500, 350}, PURPLE);
            DrawText("HELLO SHADERS", 300, 380, 30, DARKGRAY);

            if (currentShader.id > 0) EndShaderMode();

            switch (currentEffect) {
                case 0: DrawText("1: No effect  2: Grayscale  3: Invert", 50, 10, 20, DARKGRAY); break;
                case 1: DrawText("1: No effect  2: Grayscale  3: Invert  CURRENT: Grayscale", 50, 10, 20, GREEN); break;
                case 2: DrawText("1: No effect  2: Grayscale  3: Invert  CURRENT: Invert", 50, 10, 20, GREEN); break;
            }
            DrawFPS(10, 40);

        EndDrawing();
    }

    UnloadShader(grayscale);
    UnloadShader(invert);
    CloseWindow();
}

// CHALLENGE 41.1: Write a fragment shader that applies a sepia tone effect.
// Use the grayscale shader as a base, then blend with a warm color.
void challenge_sepia_shader() {
    std::cout << "Challenge 41.1 incomplete - fill in the TODOs!\n";

    // TODO: LoadShaderFromMemory(NULL, fragmentCode)
    // Sepia formula:
    //   gray = dot(texel.rgb, vec3(0.299, 0.587, 0.114))
    //   final = vec3(gray, gray, gray) * vec3(1.2, 1.0, 0.8)
    // Apply the shader and display the result

    std::cout << "Hint: Multiply gray by warm tones for sepia effect\n";
}

// CHALLENGE 41.2: Create a shader with a time uniform that animates
// a wave/ripple distortion effect.
void challenge_wave_shader() {
    std::cout << "Challenge 41.2 incomplete - fill in the TODOs!\n";

    // TODO: Create a fragment shader with uniform float uTime
    // GetShaderLocation(shader, "uTime") and SetShaderValue each frame
    // Use sin(fragTexCoord.y * frequency + uTime) * amplitude to offset pixels
    // Display the animated effect

    std::cout << "Hint: Use SetShaderValue(shader, loc, &time, SHADER_UNIFORM_FLOAT)\n";
}

void exercise_shaders_basics() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 41: Shaders Basics\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_post_processing();
    std::cout << "Example done.\n";
    challenge_sepia_shader();
    challenge_wave_shader();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 41 complete!\n";
    std::cout << "========================================\n";
}
