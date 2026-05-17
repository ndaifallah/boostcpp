#include <raylib.h>
#include <iostream>
#include <cmath>

// ============================================================
// EXERCISE 33: Sound Effects
// ============================================================

// CONCEPT: sound effects in raylib
// - InitAudioDevice(): initialize audio system
// - CloseAudioDevice(): cleanup
// - LoadSound(path): load sound file (WAV, OGG, MP3)
// - PlaySound(sound): play once
// - StopSound(sound): stop playback
// - SetSoundVolume(sound, volume): 0.0 to 1.0
// - SetSoundPitch(sound, pitch): change pitch/frequency
// - IsSoundPlaying(sound): check if still playing
// - UnloadSound(sound): free memory

// NOTE: On macOS, audio initialization is automatic via raylib.
// We generate sounds at runtime or play simple tones via
// wave generation to avoid needing external sound files.

Sound generate_tone_sound(float frequency, float duration, float volume) {
    int sampleRate = 44100;
    int frameCount = (int)(sampleRate * duration);

    short* samples = (short*)RL_MALLOC(frameCount * 2 * sizeof(short));
    if (!samples) return (Sound){0};

    for (int i = 0; i < frameCount; i++) {
        float t = (float)i / sampleRate;
        float value = sinf(2.0f * PI * frequency * t) * 32767.0f * volume;
        samples[i * 2] = (short)value;
        samples[i * 2 + 1] = (short)value;
    }

    Wave wave = {0};
    wave.data = samples;
    wave.frameCount = frameCount;
    wave.sampleRate = sampleRate;
    wave.sampleSize = 16;
    wave.channels = 2;

    return LoadSoundFromWave(wave);
}

void example_sound_basics() {
    InitAudioDevice();

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Exercise 33: Sound Basics");

    Sound beep = {0};
    bool hasFile = false;
    if (FileExists("beep.wav")) {
        beep = LoadSound("beep.wav");
        hasFile = beep.stream.buffer != NULL;
    }

    Sound tone = generate_tone_sound(440.0f, 0.3f, 0.8f);
    Sound tone_low = generate_tone_sound(220.0f, 0.5f, 0.5f);
    Sound tone_high = generate_tone_sound(880.0f, 0.2f, 0.4f);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!hasFile && IsKeyPressed(KEY_SPACE)) PlaySound(tone);
        if (IsKeyPressed(KEY_ONE)) PlaySound(tone_low);
        if (IsKeyPressed(KEY_TWO)) PlaySound(tone);
        if (IsKeyPressed(KEY_THREE)) PlaySound(tone_high);

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (hasFile) {
                DrawText("Loaded 'beep.wav' successfully!", 50, 50, 20, GREEN);
                if (IsKeyPressed(KEY_SPACE)) PlaySound(beep);
            } else {
                DrawText("Using generated tones (no sound file needed)", 50, 50, 20, DARKGRAY);
            }

            DrawText("Press 1: Low tone (220Hz)", 50, 100, 20, DARKGRAY);
            DrawText("Press 2: Mid tone (440Hz)", 50, 130, 20, DARKGRAY);
            DrawText("Press 3: High tone (880Hz)", 50, 160, 20, DARKGRAY);

            DrawText(TextFormat("Tone 1 playing: %s", IsSoundPlaying(tone_low) ? "YES" : "no"), 50, 200, 15, GRAY);
            DrawText(TextFormat("Tone 2 playing: %s", IsSoundPlaying(tone) ? "YES" : "no"), 50, 220, 15, GRAY);
            DrawText(TextFormat("Tone 3 playing: %s", IsSoundPlaying(tone_high) ? "YES" : "no"), 50, 240, 15, GRAY);

            DrawText("Press ESC to exit", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    UnloadSound(tone);
    UnloadSound(tone_low);
    UnloadSound(tone_high);
    if (hasFile) UnloadSound(beep);
    CloseWindow();
    CloseAudioDevice();
}

// CHALLENGE 33.1: Create a simple musical keyboard using the computer keyboard.
// Keys A-G play notes C-B. Show which note is playing on screen.
void challenge_musical_keyboard() {
    std::cout << "Challenge 33.1 incomplete - fill in the TODOs!\n";

    // TODO: InitAudioDevice before InitWindow
    // Generate 7 sounds for notes C, D, E, F, G, A, B (frequencies: 261, 293, 329, 349, 392, 440, 494)
    // Play note when corresponding key pressed (A=S, B=D, C=F, D=G, E=H, F=J, G=K or similar mapping)
    // Show a keyboard visual with highlighted pressed keys

    std::cout << "Hint: Sounds: C=261.63, D=293.66, E=329.63, F=349.23, G=392.00, A=440.00, B=493.88\n";
}

// CHALLENGE 33.2: Build a simple metronome with adjustable BPM.
// Ticks per beat, visual indicator, BPM adjustment with UP/DOWN arrows.
void challenge_metronome() {
    std::cout << "Challenge 33.2 incomplete - fill in the TODOs!\n";

    // TODO: InitAudioDevice before InitWindow
    // Generate a "tick" sound (short click, high freq)
    // float bpm = 120
    // float timer = 0
    // Inside game loop:
    //   float interval = 60.0 / bpm
    //   timer += GetFrameTime()
    //   if timer >= interval: PlaySound(tick), timer = 0
    //   UP/DOWN arrows adjust bpm (clamped 20-300)
    //   Display current BPM

    std::cout << "Hint: For tick, use high frequency (1000Hz) very short duration (0.01f)\n";
}

void exercise_sound_effects() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 33: Sound Effects\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_sound_basics();
    std::cout << "Example done.\n";
    challenge_musical_keyboard();
    challenge_metronome();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 33 complete!\n";
    std::cout << "========================================\n";
}
