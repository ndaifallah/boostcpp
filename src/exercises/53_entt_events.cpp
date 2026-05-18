#include "53_entt_events.h"
#include <entt/entt.hpp>
#include <iostream>

// ============================================================
// EXERCISE 53: EnTT Events & Dispatchers
// ============================================================

// CONCEPT: dispatcher decouples event producers from consumers
// - entt::dispatcher manages event routing
// - .sink<EventType>().connect<&Listener::onEvent>(listener)
// - .trigger(event) sends synchronously
// - .enqueue(event) queues for later dispatch via .update()

// Event structures (POD types with no inheritance)
struct CollisionEvent {
    entt::entity a;
    entt::entity b;
};

struct DeathEvent {
    entt::entity victim;
};

struct ScoreEvent {
    int points;
};

// Free functions for event handling (EnTT 3.x requires non-lambda callbacks)
void onCollision(const CollisionEvent &e) {
    std::cout << "Collision between entity "
              << entt::to_integral(e.a)
              << " and " << entt::to_integral(e.b) << "\n";
}

void onDeath(const DeathEvent &e) {
    std::cout << "Entity " << entt::to_integral(e.victim) << " has died!\n";
}

void onScore(const ScoreEvent &e) {
    std::cout << "Score changed by " << e.points << " points\n";
}

void example_dispatcher() {
    entt::dispatcher dispatcher;
    entt::registry registry;

    entt::entity player = registry.create();
    entt::entity enemy = registry.create();

    // Connect free functions as listeners
    dispatcher.sink<CollisionEvent>().connect<&onCollision>();
    dispatcher.sink<DeathEvent>().connect<&onDeath>();
    dispatcher.sink<ScoreEvent>().connect<&onScore>();

    // Synchronous trigger
    std::cout << "Synchronous events:\n";
    dispatcher.trigger(CollisionEvent{player, enemy});
    dispatcher.trigger(DeathEvent{enemy});
    dispatcher.trigger(ScoreEvent{100});

    // Queued dispatch
    std::cout << "\nQueued events:\n";
    dispatcher.enqueue(CollisionEvent{player, player});
    dispatcher.enqueue(ScoreEvent{50});
    dispatcher.enqueue(ScoreEvent{50});
    dispatcher.update<CollisionEvent>();
    dispatcher.update<ScoreEvent>();
}

// CHALLENGE 53.1: Create a custom event system where pressing '1', '2', '3'
// generates different events. Use a listener that counts how many of each event fires.
void challenge_event_counter() {
    std::cout << "Challenge 53.1 incomplete - fill in the TODOs!\n";

    // TODO:
    //   struct EventA {}; struct EventB {}; struct EventC {};
    //   Create dispatcher, connect counters for each
    //   Fire 5 EventA, 3 EventB, 2 EventC
    //   Print: "A: 5, B: 3, C: 2"

    std::cout << "Hint: Use separate lambdas that increment static counters\n";
}

// CHALLENGE 53.2: Use dispatcher with a registry to modify entities on events.
// When a DeathEvent fires, destroy the victim entity and emit a ScoreEvent.
void challenge_event_chain() {
    std::cout << "Challenge 53.2 incomplete - fill in the TODOs!\n";

    // TODO:
    //   dispatcher.sink<DeathEvent>().connect<[&](const DeathEvent& e) {
    //     registry.destroy(e.victim);
    //     dispatcher.enqueue(ScoreEvent{50});
    //   }>();
    //   Create entity, trigger DeathEvent on it
    //   Verify entity is dead (not valid)
    //   Verify ScoreEvent was queued

    std::cout << "Hint: Capture both dispatcher and registry by reference\n";
}

void exercise_entt_events() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 53: EnTT Events & Dispatchers\n";
    std::cout << "========================================\n";
    std::cout << "Demonstrating event-driven communication\n\n";

    example_dispatcher();
    std::cout << "\n--- Bonus Challenges ---\n";
    challenge_event_counter();
    challenge_event_chain();

    std::cout << "\n========================================\n";
    std::cout << "Exercise 53 complete!\n";
    std::cout << "========================================\n";
}
