#include <raylib.h>
#include <raymath.h>
#include <iostream>

// ============================================================
// EXERCISE 34: Music Streaming
// ============================================================

// CONCEPT: music streaming in raylib
// - LoadMusicStream(path): load music file (OGG, MP3, FLAC, XM, MOD)
// - PlayMusicStream(music): start playback
// - UpdateMusicStream(music): must call each frame to stream
// - PauseMusicStream(music) / ResumeMusicStream(music)
// - StopMusicStream(music)
// - SetMusicVolume(music, volume): 0.0 to 1.0
// - GetMusicTimePlayed(music) / GetMusicTimeLength(music)
// - IsMusicStreamPlaying(music): check state
// - SeekMusicStream(music, position): jump to position (seconds)

void example_music_basics() {
    InitAudioDevice();

    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Exercise 34: Music Basics");

    Music music = LoadMusicStream("music.ogg");
    bool hasFile = music.stream.buffer != NULL;
    float volume = 1.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (hasFile) UpdateMusicStream(music);

        if (IsKeyPressed(KEY_P)) {
            if (IsMusicStreamPlaying(music)) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }
        if (IsKeyPressed(KEY_S)) StopMusicStream(music);
        if (IsKeyPressed(KEY_R)) PlayMusicStream(music);

        if (IsKeyDown(KEY_UP)) { volume = Clamp(volume + 0.01f, 0, 1); SetMusicVolume(music, volume); }
        if (IsKeyDown(KEY_DOWN)) { volume = Clamp(volume - 0.01f, 0, 1); SetMusicVolume(music, volume); }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (hasFile) {
                float timePlayed = GetMusicTimePlayed(music);
                float timeLength = GetMusicTimeLength(music);
                float progress = (timeLength > 0) ? timePlayed / timeLength : 0;

                DrawText("Music loaded! Controls:", 50, 50, 20, GREEN);
                DrawText("P: Play/Pause   S: Stop   R: Restart", 50, 80, 20, DARKGRAY);
                DrawText("UP/DOWN: Volume", 50, 110, 20, DARKGRAY);

                DrawRectangle(50, 150, 700, 20, LIGHTGRAY);
                DrawRectangle(50, 150, (int)(700 * progress), 20, GREEN);

                int mins = (int)(timePlayed / 60);
                int secs = (int)timePlayed % 60;
                DrawText(TextFormat("Time: %02d:%02d / %02d:%02d", mins, secs,
                    (int)(timeLength / 60), (int)timeLength % 60), 50, 180, 20, DARKGRAY);

                DrawText(TextFormat("Volume: %.0f%%", volume * 100), 50, 210, 20, DARKGRAY);
                DrawText(TextFormat("Playing: %s", IsMusicStreamPlaying(music) ? "YES" : "no"), 50, 240, 20,
                    IsMusicStreamPlaying(music) ? GREEN : RED);
            } else {
                DrawText("Place 'music.ogg' in the working directory", 50, 50, 20, RED);
                DrawText("or use any .ogg/.mp3 file and rename it", 50, 80, 20, DARKGRAY);
                DrawText("Example controls shown (no audio)", 50, 130, 20, DARKGRAY);
            }

            DrawText("Press ESC to exit", 50, 400, 20, DARKGRAY);
            DrawFPS(10, 10);

        EndDrawing();
    }

    if (hasFile) UnloadMusicStream(music);
    CloseWindow();
    CloseAudioDevice();
}

// CHALLENGE 34.1: Create a simple music visualization.
// Load a music file and draw visual bars that react to the music volume.
// Use GetMusicTimePlayed() to drive animation, or use audio samples if available.
void challenge_music_visualization() {
    std::cout << "Challenge 34.1 incomplete - fill in the TODOs!\n";

    // TODO: Load a music file, display a waveform/bar visualization
    // Draw vertical bars that react to the beat.
    // Since we don't have FFT, use time-based patterns or simple amplitude pulsing.

    std::cout << "Hint: Use sin(GetMusicTimePlayed() * frequency) * amplitude for bar heights\n";
}

// CHALLENGE 34.2: Build a simple audio player with play/pause, stop,
// volume control, and a seek bar that the user can click to jump to a position.
void challenge_audio_player() {
    std::cout << "Challenge 34.2 incomplete - fill in the TODOs!\n";

    // TODO: Music music = LoadMusicStream("track.ogg")
    // Controls: P for play/pause, S for stop, UP/DOWN for volume
    // Seek bar: click on the progress bar to jump to that position
    //   if IsMouseButtonPressed(LEFT) and mouse over bar:
    //     float pos = (mouse.x - barX) / barWidth * musicLength
    //     SeekMusicStream(music, pos)
    // Display time, volume, status

    std::cout << "Hint: Use SeekMusicStream(music, position) for seeking\n";
}

void exercise_music_streaming() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 34: Music Streaming\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_music_basics();
    std::cout << "Example done.\n";
    challenge_music_visualization();
    challenge_audio_player();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 34 complete!\n";
    std::cout << "========================================\n";
}
