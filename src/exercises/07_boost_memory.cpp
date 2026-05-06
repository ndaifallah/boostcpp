#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/pool/singleton_pool.hpp>
#include <boost/pool/pool_alloc.hpp>

// ============================================================
// EXERCISE 7: Boost Memory (Pool Allocators)
// ============================================================

// CONCEPT: boost::pool
// - Simple fast memory pool for fixed-size allocations
// - Does NOT call constructors/destructors (raw memory only)
// - Ideal for POD types and arrays
// - Memory is freed when pool is destroyed

void example_boost_pool() {
    std::cout << "\n=== boost::pool Example ===\n";

    boost::pool<> pool(sizeof(int));

    std::cout << "Created pool for int-sized blocks\n";

    int* p1 = static_cast<int*>(pool.malloc());
    int* p2 = static_cast<int*>(pool.malloc());

    *p1 = 42;
    *p2 = 100;
    std::cout << "p1 = " << *p1 << ", p2 = " << *p2 << "\n";

    pool.free(p1);
    std::cout << "Freed p1\n";

    int* p3 = static_cast<int*>(pool.malloc());
    *p3 = 200;
    std::cout << "p3 (reused p1 memory) = " << *p3 << "\n";

    pool.free(p2);
    pool.free(p3);
    std::cout << "All blocks returned to pool\n";
}

// CHALLENGE 7.1: Create a boost::pool for double-sized blocks (sizeof(double)).
// Allocate 5 doubles, fill with values 1.1, 2.2, 3.3, 4.4, 5.5.
// Print them, then free all blocks.
void challenge_boost_pool() {
    std::cout << "\n--- Challenge 7.1: Pool of doubles ---\n";

    // TODO: Create a boost::pool<> for sizeof(double)

    // TODO: Allocate 5 doubles using pool.malloc()

    // TODO: Fill them with 1.1, 2.2, 3.3, 4.4, 5.5

    // TODO: Print all 5 values

    // TODO: Free all allocated blocks

    std::cout << "Challenge 7.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: boost::object_pool
// - Like pool but calls constructors/destructors automatically
// - Template parameter is the object type
// - create() constructs objects with placement new
// - Destructors called when pool is destroyed

class Widget {
public:
    Widget(int id, const std::string& name) : id_(id), name_(name) {
        std::cout << "  Widget constructed: id=" << id_ << "\n";
    }
    ~Widget() {
        std::cout << "  Widget destroyed: id=" << id_ << "\n";
    }
    void describe() const {
        std::cout << "  Widget[id=" << id_ << ", name=" << name_ << "]\n";
    }
private:
    int id_;
    std::string name_;
};

void example_object_pool() {
    std::cout << "\n=== boost::object_pool Example ===\n";

    std::cout << "Creating object_pool<Widget>\n";
    boost::object_pool<Widget> pool;

    std::cout << "Creating widgets via pool.construct():\n";
    Widget* w1 = pool.construct(1, "Alpha");
    Widget* w2 = pool.construct(2, "Beta");
    Widget* w3 = pool.construct(3, "Gamma");

    std::cout << "Calling describe():\n";
    w1->describe();
    w2->describe();
    w3->describe();

    std::cout << "Destroying pool (calls destructors):\n";
}

// CHALLENGE 7.2: Define a simple struct Point { double x, y; int id; }
// Use boost::object_pool<Point> to create 4 points at (0,0), (1,1), (2,2), (3,3).
// Print all points, then let the pool go out of scope.
void challenge_object_pool() {
    std::cout << "\n--- Challenge 7.2: Object pool with Point struct ---\n";

    // TODO: Define struct Point with x, y (double) and id (int)

    // TODO: Create boost::object_pool<Point>

    // TODO: Create 4 points at (0,0), (1,1), (2,2), (3,3) with ids 1-4

    // TODO: Print each point's coordinates and id

    // TODO: Let the pool go out of scope (destructors will run)

    std::cout << "Challenge 7.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: boost::singleton_pool
// - Global, thread-safe pool accessible from anywhere
// - Tag-based: use an empty struct as the tag
// - Memory persists until explicit release or program exit
// - Useful for frequently allocated/deallocated types

struct PlayerPoolTag {};
using PlayerPool = boost::singleton_pool<PlayerPoolTag, sizeof(int)>;

struct EnemyPoolTag {};
using EnemyPool = boost::singleton_pool<EnemyPoolTag, 64>;

void example_singleton_pool() {
    std::cout << "\n=== boost::singleton_pool Example ===\n";

    std::cout << "Allocating from singleton pools:\n";

    int* player = static_cast<int*>(PlayerPool::malloc());
    *player = 99;
    std::cout << "Player score: " << *player << "\n";

    char* enemy = static_cast<char*>(EnemyPool::malloc());
    std::strcpy(enemy, "Goblin");
    std::cout << "Enemy name: " << enemy << "\n";

    PlayerPool::free(player);
    EnemyPool::free(enemy);

    std::cout << "Released both allocations\n";
    std::cout << "Singleton pool memory persists until release_all()\n";
}

// CHALLENGE 7.3: Define two tag structs for a ConnectionPool (sizeof(double))
// and a MessagePool (128 bytes).
// Allocate from each, store values, free them, then call release_all().
void challenge_singleton_pool() {
    std::cout << "\n--- Challenge 7.3: Custom singleton pools ---\n";

    // TODO: Define ConnectionPoolTag and use singleton_pool for sizeof(double)

    // TODO: Define MessagePoolTag and use singleton_pool for 128 bytes

    // TODO: Allocate a double, set it to 3.14159, print it, free it

    // TODO: Allocate a 128-byte block, store "Hello Singleton Pool!" in it, print it, free it

    // TODO: Call release_all() on both pools

    std::cout << "Challenge 7.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: boost::pool_allocator
// - STL-compatible allocator using pool underneath
// - Can be used with std::vector, std::list, etc.
// - Faster than std::allocator for many small allocations
// - Does not call destructors on contained objects

void example_pool_allocator() {
    std::cout << "\n=== boost::pool_allocator Example ===\n";

    std::cout << "Creating vector<int, boost::pool_allocator<int>>\n";
    std::vector<int, boost::pool_allocator<int>> vec;

    for (int i = 0; i < 10; ++i) {
        vec.push_back(i * 10);
    }

    std::cout << "Vector contents: ";
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << "\n";
    std::cout << "Size: " << vec.size() << ", Capacity: " << vec.capacity() << "\n";
}

// CHALLENGE 7.4: Create a std::list<std::string, boost::pool_allocator<std::string>>
// and add 5 strings: "one", "two", "three", "four", "five".
// Print them all, then print the size.
void challenge_pool_allocator() {
    std::cout << "\n--- Challenge 7.4: List with pool_allocator ---\n";

    // TODO: Create std::list<std::string, boost::pool_allocator<std::string>>

    // TODO: Add strings: "one", "two", "three", "four", "five"

    // TODO: Print all strings

    // TODO: Print the list size

    std::cout << "Challenge 7.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_boost_memory() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 7: Boost Memory (Pool Allocators)\n";
    std::cout << "========================================\n";

    example_boost_pool();
    challenge_boost_pool();

    example_object_pool();
    challenge_object_pool();

    example_singleton_pool();
    challenge_singleton_pool();

    example_pool_allocator();
    challenge_pool_allocator();

    std::cout << "\n========================================\n";
    std::cout << "Boost Memory exercise complete!\n";
    std::cout << "========================================\n";
}
