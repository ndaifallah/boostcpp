#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <cstdint>

// ============================================================
// EXERCISE 14: ECS (Entity Component System) with STL
// ============================================================

// CONCEPT: Entity Component System Pattern
// - Entity: A unique ID representing an object (usually just an integer)
// - Component: Pure data associated with an entity (no logic)
// - System: Processes entities that have specific components
// - STL containers provide efficient storage and querying

// Entity type - just a unique identifier
using Entity = std::uint32_t;

// Component types - pure data structures
struct Position {
    float x, y, z;
};

struct Velocity {
    float vx, vy, vz;
};

struct Health {
    int current;
    int max;
};

struct Name {
    std::string value;
};

// ============================================================
// CONCEPT: Component Storage with STL
// - unordered_map<Entity, Component> for sparse component storage
// - vector<Component> with entity indexing for dense storage
// - Each approach has trade-offs in memory and access patterns

class ECSWorld {
public:
    // Entity management
    Entity createEntity() {
        return nextEntity++;
    }

    void destroyEntity(Entity e) {
        // Remove all components for this entity
        positions.erase(e);
        velocities.erase(e);
        healths.erase(e);
        names.erase(e);
    }

    // Component attachment
    Position& addPosition(Entity e, float x = 0, float y = 0, float z = 0) {
        positions[e] = {x, y, z};
        return positions[e];
    }

    Velocity& addVelocity(Entity e, float vx = 0, float vy = 0, float vz = 0) {
        velocities[e] = {vx, vy, vz};
        return velocities[e];
    }

    Health& addHealth(Entity e, int current = 100, int max = 100) {
        healths[e] = {current, max};
        return healths[e];
    }

    Name& addName(Entity e, const std::string& name) {
        names[e] = {name};
        return names[e];
    }

    // Component queries
    bool hasPosition(Entity e) const {
        return positions.find(e) != positions.end();
    }

    bool hasVelocity(Entity e) const {
        return velocities.find(e) != velocities.end();
    }

    Position* getPosition(Entity e) {
        auto it = positions.find(e);
        return it != positions.end() ? &it->second : nullptr;
    }

    Velocity* getVelocity(Entity e) {
        auto it = velocities.find(e);
        return it != velocities.end() ? &it->second : nullptr;
    }

    Health* getHealth(Entity e) {
        auto it = healths.find(e);
        return it != healths.end() ? &it->second : nullptr;
    }

    Name* getName(Entity e) {
        auto it = names.find(e);
        return it != names.end() ? &it->second : nullptr;
    }

    // System: Movement - processes entities with Position AND Velocity
    void updateMovement(float dt) {
        std::cout << "\n  [Movement System] Processing " << positions.size() << " position components...\n";
        for (auto& [entity, pos] : positions) {
            auto vel = getVelocity(entity);
            if (vel) {
                pos.x += vel->vx * dt;
                pos.y += vel->vy * dt;
                pos.z += vel->vz * dt;
                std::cout << "    Entity " << entity << " moved to (" 
                          << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
            }
        }
    }

    // System: Health Regeneration - processes entities with Health
    void updateHealthRegen() {
        std::cout << "\n  [Health System] Processing " << healths.size() << " health components...\n";
        for (auto& [entity, health] : healths) {
            if (health.current < health.max) {
                health.current = std::min(health.current + 1, health.max);
                std::cout << "    Entity " << entity << " health: " << health.current 
                          << "/" << health.max << "\n";
            }
        }
    }

    // System: Print all entities and their components
    void printAllEntities() {
        std::cout << "\n  [World State]\n";
        // Collect all unique entities
        std::vector<Entity> allEntities;
        for (const auto& [e, _] : positions) allEntities.push_back(e);
        for (const auto& [e, _] : velocities) if (std::find(allEntities.begin(), allEntities.end(), e) == allEntities.end()) allEntities.push_back(e);
        for (const auto& [e, _] : healths) if (std::find(allEntities.begin(), allEntities.end(), e) == allEntities.end()) allEntities.push_back(e);
        for (const auto& [e, _] : names) if (std::find(allEntities.begin(), allEntities.end(), e) == allEntities.end()) allEntities.push_back(e);

        for (Entity e : allEntities) {
            std::cout << "    Entity " << e;
            if (auto name = getName(e)) std::cout << " [" << name->value << "]";
            std::cout << ":\n";

            if (auto pos = getPosition(e)) {
                std::cout << "      Position: (" << pos->x << ", " << pos->y << ", " << pos->z << ")\n";
            }
            if (auto vel = getVelocity(e)) {
                std::cout << "      Velocity: (" << vel->vx << ", " << vel->vy << ", " << vel->vz << ")\n";
            }
            if (auto h = getHealth(e)) {
                std::cout << "      Health: " << h->current << "/" << h->max << "\n";
            }
        }
    }

    // Get entities that have ALL specified components (view pattern)
    std::vector<Entity> viewPositionVelocity() {
        std::vector<Entity> result;
        for (const auto& [entity, _] : positions) {
            if (velocities.count(entity)) {
                result.push_back(entity);
            }
        }
        return result;
    }

private:
    Entity nextEntity = 1;  // Start from 1 (0 can be used as invalid)
    std::unordered_map<Entity, Position> positions;
    std::unordered_map<Entity, Velocity> velocities;
    std::unordered_map<Entity, Health> healths;
    std::unordered_map<Entity, Name> names;
};

void example_ecs_basic() {
    std::cout << "\n=== Basic ECS with STL ===\n";

    ECSWorld world;

    // Create some entities
    Entity player = world.createEntity();
    world.addName(player, "Player");
    world.addPosition(player, 0, 0, 0);
    world.addVelocity(player, 1.0f, 0.5f, 0.0f);
    world.addHealth(player, 100, 100);

    Entity enemy = world.createEntity();
    world.addName(enemy, "Enemy");
    world.addPosition(enemy, 10, 10, 0);
    world.addHealth(enemy, 50, 50);

    Entity bullet = world.createEntity();
    world.addName(bullet, "Bullet");
    world.addPosition(bullet, 5, 5, 0);
    world.addVelocity(bullet, 5.0f, 0.0f, 0.0f);
    // No health component - bullets are destroyed on impact

    std::cout << "Created 3 entities: Player, Enemy, Bullet\n";
    world.printAllEntities();

    // Run systems
    std::cout << "\nRunning systems for 1 frame (dt=0.1)...\n";
    world.updateMovement(0.1f);
    world.updateHealthRegen();

    std::cout << "\nAfter 1 frame:\n";
    world.printAllEntities();
}

// CHALLENGE 14.1: Add a RenderComponent with color and size fields.
// Add a render system that prints all entities with Position AND RenderComponent.
// Create an entity with Position and RenderComponent but no Velocity.
void challenge_ecs_components() {
    std::cout << "\n--- Challenge 14.1: Add RenderComponent ---\n";

    // TODO: Define struct RenderComponent { std::string color; float size; };

    // TODO: Add renderComponents map to ECSWorld class

    // TODO: Add addRenderComponent() and getRenderComponent() methods

    // TODO: Implement render system that processes Position + RenderComponent

    // TODO: Create an entity with Position and RenderComponent, run the system

    std::cout << "Challenge 14.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Entity Views and Queries
// - Efficiently iterate entities with specific component combinations
// - STL algorithms can filter and process component sets

void example_ecs_views() {
    std::cout << "\n=== ECS Views and Queries ===\n";

    ECSWorld world;

    // Create multiple entities
    for (int i = 0; i < 5; ++i) {
        Entity e = world.createEntity();
        world.addPosition(e, static_cast<float>(i), 0, 0);
        if (i % 2 == 0) {
            world.addVelocity(e, 1.0f, 0, 0);
        }
        world.addName(e, "Entity_" + std::to_string(e));
    }

    // Query: Find all entities with Position AND Velocity (movable entities)
    auto movable = world.viewPositionVelocity();
    std::cout << "Movable entities (have Position + Velocity): " 
              << movable.size() << "\n";
    for (Entity e : movable) {
        std::cout << "  Entity " << e << " is movable\n";
    }

    // Using STL algorithms to find entities
    std::cout << "\nUsing STL find_if to locate entities with velocity:\n";
    // This demonstrates how STL integrates with ECS
}

// CHALLENGE 14.2: Implement a view that returns entities with Health component
// where health.current < health.max (damaged entities).
// Use STL algorithms (copy_if, transform) to process them.
void challenge_ecs_queries() {
    std::cout << "\n--- Challenge 14.2: Query damaged entities ---\n";

    // TODO: Create a function in ECSWorld: vector<Entity> viewDamagedEntities()

    // TODO: Use std::copy_if or similar to filter entities with current < max health

    // TODO: Test with a few entities with different health values

    std::cout << "Challenge 14.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Component Groups with vector (data-oriented design)
// - Store components in contiguous arrays for cache efficiency
// - Use parallel arrays indexed by entity ID or handle mapping

void example_ecs_data_oriented() {
    std::cout << "\n=== Data-Oriented ECS with vector ===\n";

    // Alternative: Dense component storage using vector
    struct ComponentArray {
        std::vector<Entity> entities;
        std::vector<Position> positions;
        
        void add(Entity e, const Position& p) {
            entities.push_back(e);
            positions.push_back(p);
        }
        
        Position* get(Entity e) {
            auto it = std::find(entities.begin(), entities.end(), e);
            if (it != entities.end()) {
                return &positions[std::distance(entities.begin(), it)];
            }
            return nullptr;
        }
    };

    ComponentArray posComponents;
    posComponents.add(1, {0, 0, 0});
    posComponents.add(2, {1, 1, 1});
    posComponents.add(3, {2, 2, 2});

    std::cout << "Dense storage: " << posComponents.positions.size() 
              << " components in contiguous memory\n";

    // Iterate efficiently (cache-friendly)
    std::cout << "All positions:\n";
    for (const auto& pos : posComponents.positions) {
        std::cout << "  (" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    }
}

// CHALLENGE 14.3: Implement a sparse set pattern for component storage.
// A sparse set uses two arrays: dense (contiguous components) and sparse (entity->index mapping).
// This provides O(1) lookup while keeping components contiguous.
void challenge_ecs_sparse_set() {
    std::cout << "\n--- Challenge 14.3: Sparse Set component storage ---\n";

    // TODO: Implement a SparseSet<Component> template class with:
    //   - std::vector<Component> dense;  // Contiguous storage
    //   - std::vector<Entity> dense_to_entity;  // Maps dense index to entity
    //   - std::unordered_map<Entity, size_t> sparse;  // Maps entity to dense index
    //   - insert(Entity, Component), get(Entity), remove(Entity)

    // TODO: Demonstrate adding, querying, and removing components

    std::cout << "Challenge 14.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: STL Algorithms with ECS
// - Use for_each, transform, accumulate with component data
// - Functional composition for system logic

void example_ecs_algorithms() {
    std::cout << "\n=== STL Algorithms with ECS ===\n";

    ECSWorld world;

    // Create entities with health
    for (int i = 0; i < 5; ++i) {
        Entity e = world.createEntity();
        world.addHealth(e, 50 + i * 10, 100);
        world.addName(e, "Unit_" + std::to_string(i));
    }

    std::cout << "Using STL algorithms to process health components...\n";
    // Note: In a real ECS, you'd iterate the healths map directly
    // This demonstrates the concept of algorithm-based processing
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_ecs_stl() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 14: ECS with STL\n";
    std::cout << "========================================\n";

    example_ecs_basic();
    challenge_ecs_components();

    example_ecs_views();
    challenge_ecs_queries();

    example_ecs_data_oriented();
    challenge_ecs_sparse_set();

    example_ecs_algorithms();

    std::cout << "\n========================================\n";
    std::cout << "ECS with STL exercise complete!\n";
    std::cout << "========================================\n";
}
