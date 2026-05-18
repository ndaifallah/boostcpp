#include "50_entt_basics.h"
#include <entt/entt.hpp>
#include <iostream>

// ============================================================
// EXERCISE 50: EnTT Entities (create, destroy, valid)
// ============================================================

// CONCEPT: entities are lightweight IDs managed by a registry
// - Create entities with registry.create()
// - Check validity with registry.valid(entity)
// - Destroy with registry.destroy(entity)
// - Each entity gets a unique numeric ID

void example_create_destroy_valid() {
    entt::registry registry;

    entt::entity e1 = registry.create();
    entt::entity e2 = registry.create();
    entt::entity e3 = registry.create();

    std::cout << "Created 3 entities:\n";
    std::cout << "  e1 id = " << entt::to_integral(e1) << "\n";
    std::cout << "  e2 id = " << entt::to_integral(e2) << "\n";
    std::cout << "  e3 id = " << entt::to_integral(e3) << "\n";

    std::cout << "  e1 valid: " << registry.valid(e1) << "\n";
    std::cout << "  e2 valid: " << registry.valid(e2) << "\n";
    std::cout << "  e3 valid: " << registry.valid(e3) << "\n";

    registry.destroy(e2);
    std::cout << "\nAfter destroying e2:\n";
    std::cout << "  e1 valid: " << registry.valid(e1) << "\n";
    std::cout << "  e2 valid: " << registry.valid(e2) << "\n";
    std::cout << "  e3 valid: " << registry.valid(e3) << "\n";

    entt::entity e4 = registry.create();
    std::cout << "  e4 id = " << entt::to_integral(e4) << " (recycled slot)\n";

    std::cout << "\nAlive entities: " << registry.storage<entt::entity>().size() << "\n";
}

// CHALLENGE 50.1: Batch-create 100 entities, destroy every third one,
// then count how many are still alive.
void challenge_batch_create() {
    std::cout << "Challenge 50.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Create 100 entities, store in vector
    //   Destroy indices 2,5,8,... (every third)
    //   Count alive entities
    //   Print: "Created X, destroyed Y, alive Z"

    std::cout << "Hint: Use registry.alive() or iterate to count\n";
}

// CHALLENGE 50.2: Retrieve an entity from its numeric ID using
// entt::entity{id} and check if it's still valid.
void challenge_entity_from_id() {
    std::cout << "Challenge 50.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   Create 3 entities, store their numeric IDs
    //   Destroy the second one
    //   Convert numeric IDs back to entt::entity
    //   Check and print validity of each

    std::cout << "Hint: entt::entity{static_cast<entt::id_type>(id)}\n";
}

void exercise_entt_basics() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 50: EnTT Entities\n";
    std::cout << "========================================\n";
    std::cout << "Demonstrating entity creation, destruction, and validation\n\n";

    example_create_destroy_valid();
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_batch_create();
    challenge_entity_from_id();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 50 complete!\n";
    std::cout << "========================================\n";
}
