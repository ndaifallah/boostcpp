#include "52_entt_views_groups.h"
#include <entt/entt.hpp>
#include <iostream>
#include <string>
#include <cmath>

// ============================================================
// EXERCISE 52: EnTT Views & Groups (iteration, filters)
// ============================================================

// CONCEPT: views iterate entities with specific component combinations
// - registry.view<Comp1, Comp2>() for read access
// - registry.group<Owned...>(Get...) for sorted iteration
// - Use .each() or for-loop with .begin()/.end()

struct Transform {
    float x, y, rot;
};

struct Renderable {
    int textureId;
    float depth;
};

struct Physics {
    float vx, vy;
    float mass;
};

struct TagPlayer {};
struct TagEnemy {};

void example_view_iteration() {
    entt::registry registry;

    for (int i = 0; i < 10; i++) {
        entt::entity e = registry.create();
        registry.emplace<Transform>(e, i * 10.0f, 0.0f, 0.0f);
        registry.emplace<Renderable>(e, 1, (float)i);
        if (i % 3 == 0) {
            registry.emplace<Physics>(e, 0.5f, 0.0f, 1.0f);
        }
    }

    std::cout << "Entities with Transform + Renderable:\n";
    auto view = registry.view<Transform, Renderable>();
    for (auto entity : view) {
        auto &t = view.get<Transform>(entity);
        auto &r = view.get<Renderable>(entity);
        std::cout << "  Entity " << entt::to_integral(entity)
                  << ": pos(" << t.x << ", " << t.y
                  << ") depth=" << r.depth << "\n";
    }

    std::cout << "\nEntities with Transform + Renderable + Physics:\n";
    auto view2 = registry.view<Transform, Renderable, Physics>();
    view2.each([](auto, Transform &t, Renderable &r, Physics &p) {
        std::cout << "  pos(" << t.x << "," << t.y << ") mass=" << p.mass << "\n";
    });

    std::cout << "\nEntities with Transform + Physics:\n";
    size_t physicsCount = 0;
    auto view3 = registry.view<Transform, Physics>();
    for ([[maybe_unused]] auto entity : view3) {
        physicsCount++;
    }
    std::cout << "  (" << physicsCount << " entities)\n";
}

void example_groups() {
    entt::registry registry;

    for (int i = 0; i < 10; i++) {
        entt::entity e = registry.create();
        registry.emplace<Transform>(e, (float)i, 0.0f, 0.0f);
        registry.emplace<Renderable>(e, i % 2, (float)i);
    }

    auto group = registry.group<Transform>(entt::get<Renderable>);
    std::cout << "\nGroup iteration (Transform owned, Renderable get):\n";
    for (auto entity : group) {
        auto &t = group.get<Transform>(entity);
        auto &r = group.get<Renderable>(entity);
        std::cout << "  Entity " << entt::to_integral(entity)
                  << " pos=" << t.x << " depth=" << r.depth << "\n";
    }
}

// CHALLENGE 52.1: Use tags (empty structs like TagPlayer, TagEnemy)
// to filter views. Create 5 players and 5 enemies, iterate each group separately.
void challenge_tag_filtering() {
    std::cout << "Challenge 52.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Create 10 entities with Transform
    //   5 get TagPlayer, 5 get TagEnemy
    //   Use view<Transform, TagPlayer> and view<Transform, TagEnemy>
    //   Print each group's entity IDs

    std::cout << "Hint: Tags are empty structs - use emplace<MyTag>(entity)\n";
}

// CHALLENGE 52.2: Use registry.sort to sort entities by depth (painter's algorithm).
void challenge_sort_by_depth() {
    std::cout << "Challenge 52.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Create 10 entities with Renderable (varying depth values)
    //   Use registry.sort<Renderable>([](auto lhs, auto rhs) { return lhs.depth < rhs.depth; });
    //   Iterate and verify order

    std::cout << "Hint: registry.sort<Component>(comparator) reorders pools\n";
}

void exercise_entt_views_groups() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 52: EnTT Views & Groups\n";
    std::cout << "========================================\n";
    std::cout << "Demonstrating iteration, filtering, and sorting\n\n";

    example_view_iteration();
    example_groups();
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_tag_filtering();
    challenge_sort_by_depth();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 52 complete!\n";
    std::cout << "========================================\n";
}
