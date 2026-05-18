#include "51_entt_components.h"
#include <entt/entt.hpp>
#include <iostream>
#include <string>

// ============================================================
// EXERCISE 51: EnTT Components (assign, get, remove)
// ============================================================

// CONCEPT: components are data attached to entities
// - registry.emplace<Comp>(entity, args...) to assign
// - registry.get<Comp>(entity) to access
// - registry.remove<Comp>(entity) to detach
// - registry.all_of<Comp>(entity) to check presence

struct Position {
    float x, y;
};

struct Velocity {
    float vx, vy;
};

struct Name {
    std::string value;
};

void example_component_basics() {
    entt::registry registry;

    entt::entity player = registry.create();
    registry.emplace<Position>(player, 100.0f, 200.0f);
    registry.emplace<Velocity>(player, 1.5f, 0.0f);
    registry.emplace<Name>(player, "PlayerOne");

    auto &pos = registry.get<Position>(player);
    auto &vel = registry.get<Velocity>(player);
    auto &name = registry.get<Name>(player);

    std::cout << "Player: " << name.value << "\n";
    std::cout << "  Position: (" << pos.x << ", " << pos.y << ")\n";
    std::cout << "  Velocity: (" << vel.vx << ", " << vel.vy << ")\n";

    pos.x += vel.vx;
    pos.y += vel.vy;
    std::cout << "  After update: (" << pos.x << ", " << pos.y << ")\n";

    bool hasPos = registry.all_of<Position>(player);
    bool hasVel = registry.all_of<Velocity>(player);
    std::cout << "  has Position: " << hasPos << "\n";
    std::cout << "  has Velocity: " << hasVel << "\n";

    registry.remove<Velocity>(player);
    hasVel = registry.all_of<Velocity>(player);
    std::cout << "  has Velocity after remove: " << hasVel << "\n";
}

// CHALLENGE 51.1: Create entities with a Health component (int current, int max).
// Print all entities whose health is below 50% of max.
void challenge_health_check() {
    std::cout << "Challenge 51.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct Health { int current; int max; };
    //   Create 10 entities with random health values
    //   Print entities where current < max * 0.5f

    std::cout << "Hint: Use registry.get<Health>(entity) and compare\n";
}

// CHALLENGE 51.2: Use registry.emplace_or_replace and registry.patch
// to safely update components.
void challenge_emplace_patch() {
    std::cout << "Challenge 51.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Create an entity
    //   Use emplace_or_replace to set Position twice
    //   Use patch<Position>(entity, [](auto& p) { p.x = 42; });
    //   Print final position

    std::cout << "Hint: emplace_or_replace returns a reference to the component\n";
}

void exercise_entt_components() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 51: EnTT Components\n";
    std::cout << "========================================\n";
    std::cout << "Demonstrating component assignment, access, and removal\n\n";

    example_component_basics();
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_health_check();
    challenge_emplace_patch();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 51 complete!\n";
    std::cout << "========================================\n";
}
