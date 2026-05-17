#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <optional>
#include <cassert>

// ============================================================
// EXERCISE 19: Skip Lists
// ============================================================

// CONCEPT: Skip Lists
// - Probabilistic data structure for sorted data
// - Multiple layers of linked lists for O(log n) average operations
// - Used by Redis for sorted sets (ZSET)
// - Simpler to implement than balanced trees (no rotations)
// - Each element has a random height (number of levels)
// - Higher levels act as "express lanes" for fast traversal

// ============================================================
// Skip List Implementation
// ============================================================

template<typename K, typename V>
struct SkipNode {
    K key;
    V value;
    std::vector<SkipNode*> forward;

    SkipNode(const K& k, const V& v, int level)
        : key(k), value(v), forward(level + 1, nullptr) {}
};

template<typename K, typename V>
class SkipList {
    static constexpr int MAX_LEVEL = 16;
    static constexpr float PROBABILITY = 0.5f;

    SkipNode<K, V>* head;
    int current_level;
    std::mt19937 rng;
    std::uniform_real_distribution<float> dist;

    int random_level() {
        int level = 0;
        while (dist(rng) < PROBABILITY && level < MAX_LEVEL) {
            level++;
        }
        return level;
    }

public:
    SkipList() : current_level(0), rng(42), dist(0.0f, 1.0f) {
        head = new SkipNode<K, V>(K{}, V{}, MAX_LEVEL);
    }

    ~SkipList() {
        SkipNode<K, V>* current = head->forward[0];
        while (current) {
            auto next = current->forward[0];
            delete current;
            current = next;
        }
        delete head;
    }

    void insert(const K& key, const V& value) {
        std::vector<SkipNode<K, V>*> update(MAX_LEVEL + 1);
        SkipNode<K, V>* current = head;

        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current && current->key == key) {
            current->value = value;
            return;
        }

        int new_level = random_level();
        if (new_level > current_level) {
            for (int i = current_level + 1; i <= new_level; i++) {
                update[i] = head;
            }
            current_level = new_level;
        }

        SkipNode<K, V>* new_node = new SkipNode<K, V>(key, value, new_level);
        for (int i = 0; i <= new_level; i++) {
            new_node->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = new_node;
        }
    }

    std::optional<V> find(const K& key) const {
        SkipNode<K, V>* current = head;

        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        if (current && current->key == key) {
            return current->value;
        }
        return std::nullopt;
    }

    bool remove(const K& key) {
        std::vector<SkipNode<K, V>*> update(MAX_LEVEL + 1);
        SkipNode<K, V>* current = head;

        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (!current || current->key != key) {
            return false;
        }

        for (int i = 0; i <= current_level; i++) {
            if (update[i]->forward[i] != current) break;
            update[i]->forward[i] = current->forward[i];
        }

        delete current;

        while (current_level > 0 && !head->forward[current_level]) {
            current_level--;
        }

        return true;
    }

    void print_structure() const {
        std::cout << "Skip List Structure (levels " << current_level << " to 0):\n";

        for (int i = current_level; i >= 0; i--) {
            std::cout << "  L" << i << ": ";
            SkipNode<K, V>* current = head->forward[i];
            while (current) {
                std::cout << "[" << current->key << ":" << current->value << "] -> ";
                current = current->forward[i];
            }
            std::cout << "NIL\n";
        }
    }

    void print_sorted() const {
        SkipNode<K, V>* current = head->forward[0];
        while (current) {
            std::cout << "  [" << current->key << ": " << current->value << "]\n";
            current = current->forward[0];
        }
    }

    int size() const {
        int count = 0;
        SkipNode<K, V>* current = head->forward[0];
        while (current) {
            count++;
            current = current->forward[0];
        }
        return count;
    }

    bool empty() const {
        return head->forward[0] == nullptr;
    }

    std::vector<std::pair<K, V>> range(const K& start, const K& end) const {
        std::vector<std::pair<K, V>> result;
        SkipNode<K, V>* current = head;

        for (int i = current_level; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < start) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        while (current && current->key <= end) {
            result.push_back({current->key, current->value});
            current = current->forward[0];
        }

        return result;
    }
};

// ============================================================
// EXAMPLE: Basic skip list operations

void example_basic_operations() {
    std::cout << "\n=== Basic Skip List Operations ===\n";

    SkipList<int, std::string> sl;

    sl.insert(3, "three");
    sl.insert(6, "six");
    sl.insert(1, "one");
    sl.insert(9, "nine");
    sl.insert(4, "four");

    std::cout << "Inserted: 3, 6, 1, 9, 4\n";
    sl.print_structure();

    std::cout << "\nSorted order:\n";
    sl.print_sorted();

    if (auto val = sl.find(6)) {
        std::cout << "\nFound key 6: " << *val << "\n";
    }

    if (!sl.find(5)) {
        std::cout << "Key 5 not found\n";
    }

    sl.remove(4);
    std::cout << "\nAfter removing 4:\n";
    sl.print_sorted();
}

// CHALLENGE 19.1: Create a SkipList<std::string, int> for a phone book.
// Add: {"Alice", 5550101}, {"Bob", 5550202}, {"Charlie", 5550303},
//      {"Diana", 5550404}, {"Eve", 5550505}.
// Look up and print Bob's number.
// Remove Charlie and print all remaining entries in sorted order.
void challenge_phone_book() {
    std::cout << "\n--- Challenge 19.1: Phone book ---\n";

    // TODO: Create SkipList<std::string, int>

    // TODO: Add the five contacts

    // TODO: Look up and print Bob's number

    // TODO: Remove Charlie

    // TODO: Print all remaining entries in sorted order

    std::cout << "Challenge 19.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// EXAMPLE: Range queries (like Redis ZRANGEBYSCORE)

void example_range_queries() {
    std::cout << "\n=== Range Queries ===\n";

    SkipList<int, std::string> scores;

    scores.insert(10, "Alice");
    scores.insert(25, "Bob");
    scores.insert(30, "Charlie");
    scores.insert(45, "Diana");
    scores.insert(50, "Eve");
    scores.insert(60, "Frank");
    scores.insert(75, "Grace");

    std::cout << "All scores:\n";
    scores.print_sorted();

    std::cout << "\nScores in range [25, 60]:\n";
    auto range = scores.range(25, 60);
    for (const auto& [score, name] : range) {
        std::cout << "  " << score << ": " << name << "\n";
    }

    std::cout << "\nScores in range [40, 55]:\n";
    range = scores.range(40, 55);
    for (const auto& [score, name] : range) {
        std::cout << "  " << score << ": " << name << "\n";
    }
}

// CHALLENGE 19.2: Create a SkipList<int, std::string> representing
// a leaderboard with scores as keys and player names as values.
// Add at least 8 players with scores from 100 to 1000.
// Query and print players with scores in range [300, 700].
// Query and print players with scores in range [800, 900].
void challenge_leaderboard() {
    std::cout << "\n--- Challenge 19.2: Game leaderboard ---\n";

    // TODO: Create SkipList<int, std::string>

    // TODO: Add at least 8 players with scores 100-1000

    // TODO: Query range [300, 700] and print

    // TODO: Query range [800, 900] and print

    std::cout << "Challenge 19.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// EXAMPLE: Update existing values

void example_update_values() {
    std::cout << "\n=== Updating Values ===\n";

    SkipList<std::string, int> inventory;

    inventory.insert("apples", 50);
    inventory.insert("bananas", 30);
    inventory.insert("oranges", 40);

    std::cout << "Initial inventory:\n";
    inventory.print_sorted();

    inventory.insert("bananas", 45);
    std::cout << "\nAfter updating bananas to 45:\n";
    inventory.print_sorted();

    if (auto val = inventory.find("bananas")) {
        std::cout << "Bananas in stock: " << *val << "\n";
    }
}

// CHALLENGE 19.3: Create a SkipList<std::string, double> for stock prices.
// Add: {"AAPL", 150.0}, {"GOOGL", 2800.0}, {"MSFT", 300.0}, {"AMZN", 3300.0}.
// Update GOOGL to 2850.0 and MSFT to 310.0.
// Print all stock prices. Look up and print AAPL's price.
void challenge_stock_prices() {
    std::cout << "\n--- Challenge 19.3: Stock price tracker ---\n";

    // TODO: Create SkipList<std::string, double>

    // TODO: Add the four stocks with initial prices

    // TODO: Update GOOGL to 2850.0 and MSFT to 310.0

    // TODO: Print all stock prices

    // TODO: Look up and print AAPL's price

    std::cout << "Challenge 19.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// EXAMPLE: Skip list vs flat_map comparison

void example_comparison_with_flatmap() {
    std::cout << "\n=== Skip List vs flat_map Comparison ===\n";

    std::cout << "Skip List characteristics:\n";
    std::cout << "  - O(log n) average insert/delete/lookup\n";
    std::cout << "  - No memory reallocation on insert\n";
    std::cout << "  - Each node has multiple forward pointers\n";
    std::cout << "  - Probabilistic balancing (no rotations)\n";
    std::cout << "  - Used by Redis for sorted sets\n";

    std::cout << "\nBoost flat_map characteristics:\n";
    std::cout << "  - O(log n) lookup, O(n) insert/delete\n";
    std::cout << "  - Contiguous memory (better cache locality)\n";
    std::cout << "  - Single vector internally\n";
    std::cout << "  - Sorted order maintained\n";
    std::cout << "  - Best for read-heavy, small/medium datasets\n";

    SkipList<int, int> sl;
    for (int i = 0; i < 20; i++) {
        sl.insert(i, i * 10);
    }

    std::cout << "\nSkip list with 20 elements:\n";
    std::cout << "  Size: " << sl.size() << "\n";
    std::cout << "  Max level used: " << 16 << "\n";

    if (auto val = sl.find(15)) {
        std::cout << "  Found key 15: " << *val << "\n";
    }
}

// CHALLENGE 19.4: Insert 100 random integers (0-999) into a SkipList<int, int>.
// Count how many unique keys were inserted (duplicates should update).
// Print the final size.
// Then remove all even numbers and print the new size.
void challenge_bulk_operations() {
    std::cout << "\n--- Challenge 19.4: Bulk operations ---\n";

    // TODO: Create SkipList<int, int>

    // TODO: Insert 100 random integers (0-999)

    // TODO: Print final size (unique keys)

    // TODO: Remove all even numbers (iterate and remove)

    // TODO: Print new size

    std::cout << "Challenge 19.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Why Redis uses Skip Lists
// - In-memory data structure (no disk I/O concerns)
// - Need efficient range queries for ZRANGEBYSCORE, ZREVRANGE
// - Simpler to implement than balanced trees
// - Good concurrency characteristics
// - Memory overhead acceptable for in-memory database
// - Alternative to B+ trees (which are better for disk)

void example_redis_use_case() {
    std::cout << "\n=== Redis Sorted Set Simulation ===\n";

    SkipList<double, std::string> sorted_set;

    std::cout << "ZADD myset 100.0 \"player1\"\n";
    sorted_set.insert(100.0, "player1");
    std::cout << "ZADD myset 250.5 \"player2\"\n";
    sorted_set.insert(250.5, "player2");
    std::cout << "ZADD myset 175.3 \"player3\"\n";
    sorted_set.insert(175.3, "player3");
    std::cout << "ZADD myset 300.0 \"player4\"\n";
    sorted_set.insert(300.0, "player4");
    std::cout << "ZADD myset 200.0 \"player5\"\n";
    sorted_set.insert(200.0, "player5");

    std::cout << "\nZRANGE myset 0 -1 (all elements by score):\n";
    sorted_set.print_sorted();

    std::cout << "\nZRANGEBYSCORE myset 150 250:\n";
    auto range = sorted_set.range(150.0, 250.0);
    for (const auto& [score, member] : range) {
        std::cout << "  " << score << ": " << member << "\n";
    }

    std::cout << "\nZREM myset \"player3\"\n";
    sorted_set.remove(175.3);

    std::cout << "After removal:\n";
    sorted_set.print_sorted();

    std::cout << "\nZCARD myset: " << sorted_set.size() << "\n";
}

// CHALLENGE 19.5: Simulate a Redis sorted set for a real-time ranking system.
// Add 10 users with scores representing their points.
// Use ZRANGEBYSCORE to find users with points between 500 and 800.
// Update one user's score using ZADD (insert with same key).
// Remove the lowest scoring user.
// Print the final ranking.
void challenge_ranking_system() {
    std::cout << "\n--- Challenge 19.5: Real-time ranking system ---\n";

    // TODO: Create SkipList<double, std::string>

    // TODO: Add 10 users with scores (points)

    // TODO: Find users with scores between 500 and 800

    // TODO: Update one user's score (insert with same key)

    // TODO: Remove the lowest scoring user

    // TODO: Print final ranking

    std::cout << "Challenge 19.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_skip_lists() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 19: Skip Lists\n";
    std::cout << "========================================\n";

    example_basic_operations();
    challenge_phone_book();

    example_range_queries();
    challenge_leaderboard();

    example_update_values();
    challenge_stock_prices();

    example_comparison_with_flatmap();
    challenge_bulk_operations();

    example_redis_use_case();
    challenge_ranking_system();

    std::cout << "\n========================================\n";
    std::cout << "Skip Lists exercise complete!\n";
    std::cout << "========================================\n";
}
