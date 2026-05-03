#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================
// EXERCISE 1: Smart Pointers
// ============================================================

// CONCEPT: unique_ptr
// - Owns an object exclusively
// - Cannot be copied, only moved
// - Automatically deletes when it goes out of scope
// - Zero overhead compared to raw pointers

void example_unique_ptr() {
    std::cout << "\n=== unique_ptr Examples ===\n";

    // Basic usage
    std::unique_ptr<int> p1 = std::make_unique<int>(42);
    std::cout << "p1: " << *p1 << "\n";

    // Transfer ownership (move, not copy)
    std::unique_ptr<int> p2 = std::move(p1);
    std::cout << "After move, p2: " << *p2 << "\n";
    // p1 is now nullptr

    // With dynamic objects
    struct Point {
        int x, y;
        Point(int x, int y) : x(x), y(y) {}
        ~Point() { std::cout << "Point(" << x << "," << y << ") destroyed\n"; }
    };

    auto p3 = std::make_unique<Point>(10, 20);
    std::cout << "Point: (" << p3->x << ", " << p3->y << ")\n";
}

// CHALLENGE 1.1: Create a unique_ptr to a std::string, print it,
// then transfer it to another unique_ptr
void challenge_unique_ptr() {
    std::cout << "\n--- Challenge 1.1: unique_ptr with string ---\n";

    // TODO: Create a unique_ptr<string> with make_unique containing "Hello C++"
    // auto str_ptr = std::make_unique<std::string>("...");

    // TODO: Print the string content

    // TODO: Transfer ownership to another unique_ptr using std::move

    // TODO: Print from the new unique_ptr

    // TODO: Verify the original is nullptr (hint: use .get() or compare with nullptr)

    std::cout << "Challenge 1.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: shared_ptr
// - Multiple pointers can own the same object
// - Reference counted - deleted when last owner is destroyed
// - Slight overhead for the reference count
// - Use make_shared for efficiency (single allocation)

void example_shared_ptr() {
    std::cout << "\n=== shared_ptr Examples ===\n";

    struct Widget {
        std::string name;
        Widget(const std::string& n) : name(n) {
            std::cout << "Widget '" << name << "' created\n";
        }
        ~Widget() { std::cout << "Widget '" << name << "' destroyed\n"; }
    };

    auto s1 = std::make_shared<Widget>("Alpha");
    std::cout << "Reference count: " << s1.use_count() << "\n";

    {
        auto s2 = s1; // Copy increases reference count
        std::cout << "Reference count after copy: " << s1.use_count() << "\n";
        std::cout << "Both point to: " << s1->name << " and " << s2->name << "\n";
    } // s2 destroyed, count decreases

    std::cout << "Reference count after s2 destroyed: " << s1.use_count() << "\n";
    // Widget destroyed here when s1 goes out of scope
}

// CHALLENGE 1.2: Create shared_ptrs, pass them to a function,
// observe reference counting
void challenge_shared_ptr() {
    std::cout << "\n--- Challenge 1.2: shared_ptr reference counting ---\n";

    // TODO: Create a shared_ptr<int> with value 100

    // TODO: Print use_count() (should be 1)

    // TODO: Create another shared_ptr that shares ownership

    // TODO: Print use_count() (should be 2)

    // TODO: Create a third shared_ptr that shares ownership

    // TODO: Print use_count() (should be 3)

    std::cout << "Challenge 1.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: weak_ptr
// - Non-owning observer of a shared_ptr
// - Does not affect reference count
// - Use lock() to get a temporary shared_ptr (returns nullptr if expired)
// - Solves circular reference memory leaks

void example_weak_ptr() {
    std::cout << "\n=== weak_ptr Examples ===\n";

    auto shared = std::make_shared<std::string>("I am shared!");
    std::weak_ptr<std::string> weak = shared;

    std::cout << "weak.expired(): " << weak.expired() << "\n";
    std::cout << "weak.use_count(): " << weak.use_count() << "\n";

    // Safe access via lock()
    if (auto locked = weak.lock()) {
        std::cout << "Via weak.lock(): " << *locked << "\n";
    }

    shared.reset(); // Destroy the object

    std::cout << "After reset, weak.expired(): " << weak.expired() << "\n";
    if (auto locked = weak.lock()) {
        std::cout << "This won't print\n";
    } else {
        std::cout << "Object is gone!\n";
    }
}

// CHALLENGE 1.3: Demonstrate weak_ptr with a simple cache pattern
// - Create a shared_ptr to some data
// - Create a weak_ptr observer
// - Check if data is available via weak_ptr
void challenge_weak_ptr() {
    std::cout << "\n--- Challenge 1.3: weak_ptr cache pattern ---\n";

    // TODO: Create a shared_ptr to a vector<int> with values {1, 2, 3, 4, 5}

    // TODO: Create a weak_ptr from it

    // TODO: Write logic: if the data exists (use lock()), print its contents
    //       Otherwise print "Cache miss"

    // TODO: Reset the shared_ptr and try again (should print "Cache miss")

    std::cout << "Challenge 1.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Custom deleters
// - unique_ptr can use custom deleters for special cleanup
// - Useful for FILE*, sockets, memory pools, etc.

void example_custom_deleter() {
    std::cout << "\n=== Custom Deleter Example ===\n";

    // Using unique_ptr with a custom deleter
    auto deleter = [](int* p) {
        std::cout << "Custom deleter called for " << *p << "\n";
        delete p;
    };

    std::unique_ptr<int, decltype(deleter)> ptr(new int(99), deleter);
    std::cout << "Value: " << *ptr << "\n";
    // Custom deleter called automatically when ptr is destroyed
}

// CHALLENGE 1.4: Create a unique_ptr with a custom deleter that
// prints "Cleaning up resource!" before deleting
void challenge_custom_deleter() {
    std::cout << "\n--- Challenge 1.4: Custom deleter ---\n";

    // TODO: Define a lambda deleter that prints "Cleaning up resource!" then deletes

    // TODO: Create a unique_ptr to a double (value 3.14) with the custom deleter

    // TODO: Print the value

    // TODO: (Optional) Try creating a unique_ptr<FILE> using fopen/fclose
    //       as a custom deleter for RAII file handling

    std::cout << "Challenge 1.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_smart_pointers() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 1: Smart Pointers\n";
    std::cout << "========================================\n";

    example_unique_ptr();
    challenge_unique_ptr();

    example_shared_ptr();
    challenge_shared_ptr();

    example_weak_ptr();
    challenge_weak_ptr();

    example_custom_deleter();
    challenge_custom_deleter();

    std::cout << "\n========================================\n";
    std::cout << "Smart Pointers exercise complete!\n";
    std::cout << "========================================\n";
}
