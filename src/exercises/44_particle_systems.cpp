#include <raylib.h>
#include <iostream>
#include <vector>
#include <cmath>

// ============================================================
// EXERCISE 44: Particle Systems
// ============================================================

// CONCEPT: particle systems
// - Particles are small sprites/shapes with position, velocity, lifetime
// - Each frame: update position, decrease lifetime, draw
// - Dead particles are recycled when new ones are emitted
// - Useful for: fire, smoke, explosions, rain, snow, sparks

struct Particle {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float life;
    float maxLife;
    float size;
};

struct ParticleSystem {
    std::vector<Particle> particles;
    int maxParticles;
};

void init_particle(Particle& p, Vector2 pos, Color color, float life) {
    p.position = pos;
    p.velocity = {(float)GetRandomValue(-100, 100) / 100.0f * 200.0f,
                  (float)GetRandomValue(-200, 0) / 100.0f * 200.0f};
    p.color = color;
    p.life = life;
    p.maxLife = life;
    p.size = (float)GetRandomValue(2, 6);
}

void update_particles(ParticleSystem& ps, float dt, Vector2 emitter) {
    for (int i = 0; i < ps.particles.size(); i++) {
        ps.particles[i].position.x += ps.particles[i].velocity.x * dt;
        ps.particles[i].position.y += ps.particles[i].velocity.y * dt;
        ps.particles[i].velocity.y += 200.0f * dt;
        ps.particles[i].life -= dt;
        ps.particles[i].color.a = (unsigned char)(255 * (ps.particles[i].life / ps.particles[i].maxLife));
    }

    int dead = 0;
    for (auto& p : ps.particles) {
        if (p.life <= 0) {
            init_particle(p, emitter, ORANGE, (float)GetRandomValue(5, 15) / 10.0f);
            dead++;
        }
    }
}

void draw_particles(const ParticleSystem& ps) {
    for (const auto& p : ps.particles) {
        DrawCircle((int)p.position.x, (int)p.position.y, p.size, p.color);
    }
}

void example_particle_system() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Exercise 44: Particle System");

    ParticleSystem ps;
    ps.maxParticles = 200;
    for (int i = 0; i < ps.maxParticles; i++) {
        Particle p;
        init_particle(p, (Vector2){400, 350}, ORANGE, (float)GetRandomValue(5, 15) / 10.0f);
        ps.particles.push_back(p);
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        update_particles(ps, GetFrameTime(), mouse);

        BeginDrawing();
            ClearBackground(BLACK);

            draw_particles(ps);

            DrawText("Particle System - mouse moves emitter", 50, 10, 20, WHITE);
            DrawText(TextFormat("Particles: %zu", ps.particles.size()), 50, 400, 20, WHITE);
            DrawFPS(10, 40);

        EndDrawing();
    }

    CloseWindow();
}

// CHALLENGE 44.1: Create a rain effect with particles falling from the top.
// Recycle dead particles at random X positions at the top of the screen.
void challenge_rain_effect() {
    std::cout << "Challenge 44.1 incomplete - fill in the TODOs!\n";

    // TODO: 300 particles, spawn at random x positions at y = -10
    // velocity = {0, 200 + random * 200} (downward)
    // Draw as thin lines (DrawLine or DrawLineEx) for rain look
    // Color: fade blue or white

    std::cout << "Hint: Use DrawLineEx from particle position to position + velocity*0.1 for streak\n";
}

// CHALLENGE 44.2: Create a fireworks explosion effect.
// When mouse is clicked, spawn 50 particles that explode outward.
// Use gravity to pull them down, fade them out.
void challenge_fireworks() {
    std::cout << "Challenge 44.2 incomplete - fill in the TODOs!\n";

    // TODO: On click, create 50 particles at mouse position
    // velocity: random direction (angle) with random speed
    // Color: randomized bright colors
    // Fade out over 1-2 seconds

    std::cout << "Hint: vx = cos(angle) * speed, vy = sin(angle) * speed, speed = 50-300\n";
}

void exercise_particle_systems() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 44: Particle Systems\n";
    std::cout << "========================================\n";
    std::cout << "Opening examples - close each window to continue...\n\n";

    example_particle_system();
    std::cout << "Example done.\n";
    challenge_rain_effect();
    challenge_fireworks();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 44 complete!\n";
    std::cout << "========================================\n";
}
