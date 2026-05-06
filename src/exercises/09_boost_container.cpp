#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <boost/container/flat_map.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/string.hpp>

// ============================================================
// EXERCISE 9: Boost Container
// ============================================================

// CONCEPT: flat_map and flat_set
// - Implemented as sorted vectors instead of tree nodes
// - Better cache locality, faster iteration, less memory
// - O(n) insertion/deletion, O(log n) lookup
// - Ideal when reads >> writes, or for small/medium datasets

void example_flat_map() {
    std::cout << "\n=== flat_map Example ===\n";

    boost::container::flat_map<std::string, int> scores;

    scores["Alice"] = 95;
    scores["Bob"] = 87;
    scores["Charlie"] = 92;
    scores["Diana"] = 98;

    std::cout << "All scores (sorted by name):\n";
    for (const auto& [name, score] : scores) {
        std::cout << "  " << name << ": " << score << "\n";
    }

    std::cout << "Bob's score: " << scores.at("Bob") << "\n";

    std::cout << "Keys are stored in sorted order:\n";
    for (const auto& pair : scores) {
        std::cout << "  " << pair.first << "\n";
    }
}

// CHALLENGE 9.1: Create a flat_map<int, std::string> mapping employee IDs to names.
// Add: {101, "John"}, {105, "Jane"}, {103, "Jim"}, {102, "Jill"}.
// Print all entries (they should be sorted by ID).
// Then look up and print the name for ID 103.
void challenge_flat_map() {
    std::cout << "\n--- Challenge 9.1: Employee directory ---\n";

    // TODO: Create flat_map<int, std::string>

    // TODO: Add the four employees with IDs 101, 105, 103, 102

    // TODO: Print all entries (should be sorted by ID)

    // TODO: Look up and print the name for ID 103

    std::cout << "Challenge 9.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: flat_set
// - Sorted vector with unique elements
// - Faster than std::set for iteration and memory usage
// - Set operations: intersection, union, difference available

void example_flat_set() {
    std::cout << "\n=== flat_set Example ===\n";

    boost::container::flat_set<int> set1 = {1, 3, 5, 7, 9};
    boost::container::flat_set<int> set2 = {2, 3, 5, 8, 9};

    std::cout << "set1: ";
    for (auto v : set1) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "set2: ";
    for (auto v : set2) std::cout << v << " ";
    std::cout << "\n";

    std::vector<int> result;

    std::set_intersection(set1.begin(), set1.end(),
                          set2.begin(), set2.end(),
                          std::back_inserter(result));
    std::cout << "Intersection: ";
    for (auto v : result) std::cout << v << " ";
    std::cout << "\n";

    result.clear();
    std::set_union(set1.begin(), set1.end(),
                   set2.begin(), set2.end(),
                   std::back_inserter(result));
    std::cout << "Union: ";
    for (auto v : result) std::cout << v << " ";
    std::cout << "\n";
}

// CHALLENGE 9.2: Create two flat_sets of strings:
//   languages1: {"C++", "Python", "Rust", "Go"}
//   languages2: {"Python", "Java", "Go", "Swift"}
// Find and print the intersection (languages in both sets).
// Find and print the difference (languages in set1 but not set2).
void challenge_flat_set() {
    std::cout << "\n--- Challenge 9.2: Set operations on strings ---\n";

    // TODO: Create flat_set<std::string> languages1 with C++, Python, Rust, Go

    // TODO: Create flat_set<std::string> languages2 with Python, Java, Go, Swift

    // TODO: Find intersection and print common languages

    // TODO: Find difference (set1 - set2) and print

    std::cout << "Challenge 9.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: stable_vector
// - Like std::vector but pointers/references remain valid after insert/erase
// - Implemented as a list of contiguous blocks
// - No iterator invalidation on insertion/deletion (except erased element)
// - Slightly slower access due to indirection

void example_stable_vector() {
    std::cout << "\n=== stable_vector Example ===\n";

    boost::container::stable_vector<int> vec;

    for (int i = 0; i < 5; ++i) {
        vec.push_back(i * 10);
    }

    std::cout << "Initial vector: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";

    int* ptr = &vec[2];
    int& ref = vec[2];
    std::cout << "Before insert: *ptr = " << *ptr << ", ref = " << ref << "\n";

    vec.insert(vec.begin(), 999);

    std::cout << "After inserting 999 at front: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "After insert: *ptr = " << *ptr << ", ref = " << ref << "\n";
    std::cout << "Pointer/reference still valid!\n";
}

// CHALLENGE 9.3: Create a stable_vector of strings with {"alpha", "beta", "gamma"}.
// Store a pointer to "beta". Insert "delta" at the beginning.
// Verify the pointer to "beta" is still valid and print its value.
// Then erase "gamma" and print the remaining elements.
void challenge_stable_vector() {
    std::cout << "\n--- Challenge 9.3: Stable vector pointer safety ---\n";

    // TODO: Create stable_vector<std::string> with alpha, beta, gamma

    // TODO: Store a pointer to the "beta" element

    // TODO: Insert "delta" at the beginning

    // TODO: Verify pointer to "beta" is still valid and print it

    // TODO: Erase "gamma" and print remaining elements

    std::cout << "Challenge 9.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: static_vector
// - Fixed-capacity vector with no dynamic allocation
// - Stores elements in-place (on the stack or embedded in object)
// - Useful when max size is known at compile time
// - Similar to std::array but with variable size

void example_static_vector() {
    std::cout << "\n=== static_vector Example ===\n";

    boost::container::static_vector<int, 8> vec;

    std::cout << "Capacity: " << vec.capacity() << "\n";
    std::cout << "Initial size: " << vec.size() << "\n";

    for (int i = 0; i < 5; ++i) {
        vec.push_back(i * i);
    }

    std::cout << "Size after 5 pushes: " << vec.size() << "\n";
    std::cout << "Contents: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";

    vec.pop_back();
    std::cout << "After pop_back: size = " << vec.size() << "\n";

    std::cout << "Max elements: " << vec.max_size() << "\n";
}

// CHALLENGE 9.4: Create a static_vector<double, 10>.
// Fill it with values 0.0, 0.5, 1.0, ..., 4.5 (10 values).
// Print size, capacity, and all values.
// Then try to push_back one more value and handle the error.
void challenge_static_vector() {
    std::cout << "\n--- Challenge 9.4: Static vector with doubles ---\n";

    // TODO: Create static_vector<double, 10>

    // TODO: Fill with 10 values from 0.0 to 4.5 (step 0.5)

    // TODO: Print size, capacity, and all values

    // TODO: Try push_back of one more value and catch the exception

    std::cout << "Challenge 9.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: small_vector
// - Like static_vector but falls back to heap when capacity exceeded
// - First N elements stored inline (no allocation)
// - Best of both worlds: stack for small, heap for large
// - Commonly used in compilers, parsers, small collections

void example_small_vector() {
    std::cout << "\n=== small_vector Example ===\n";

    boost::container::small_vector<int, 4> vec;

    std::cout << "Inline capacity: " << vec.capacity() << "\n";

    for (int i = 0; i < 3; ++i) {
        vec.push_back(i);
        std::cout << "After push " << i << ": size=" << vec.size()
                  << ", capacity=" << vec.capacity() << "\n";
    }

    std::cout << "Adding 5th element (may allocate):\n";
    vec.push_back(3);
    std::cout << "After push 3: size=" << vec.size()
              << ", capacity=" << vec.capacity() << "\n";

    std::cout << "Contents: ";
    for (auto v : vec) std::cout << v << " ";
    std::cout << "\n";
}

// CHALLENGE 9.5: Create a small_vector<std::string, 2>.
// Add "one", "two" (should be inline). Print capacity.
// Add "three", "four", "five". Print capacity again.
// Print all elements.
void challenge_small_vector() {
    std::cout << "\n--- Challenge 9.5: Small vector with strings ---\n";

    // TODO: Create small_vector<std::string, 2>

    // TODO: Add "one" and "two", print capacity

    // TODO: Add "three", "four", "five", print capacity

    // TODO: Print all elements

    std::cout << "Challenge 9.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: boost::container::string
// - SSO (Small String Optimization) with configurable small size
// - Better performance than std::string for small strings
// - Same interface as std::string
// - Small strings stored inline without allocation

void example_boost_string() {
    std::cout << "\n=== boost::container::string Example ===\n";

    boost::container::string s1 = "Hello";
    boost::container::string s2(" World");

    std::cout << "s1: " << s1 << "\n";
    std::cout << "s2: " << s2 << "\n";

    s1 += s2;
    std::cout << "Concatenated: " << s1 << "\n";

    std::cout << "Length: " << s1.size() << "\n";
    std::cout << "Capacity: " << s1.capacity() << "\n";

    boost::container::string s3 = "Short";
    boost::container::string s4 = "This is a much longer string that exceeds SSO buffer";

    std::cout << "Short string capacity: " << s3.capacity() << "\n";
    std::cout << "Long string capacity: " << s4.capacity() << "\n";
}

// CHALLENGE 9.6: Create a boost::container::string with "Boost Container".
// Find the position of "Container" and replace it with "String".
// Print the result. Append " is great!" and print again.
void challenge_boost_string() {
    std::cout << "\n--- Challenge 9.6: String manipulation ---\n";

    // TODO: Create boost::container::string with "Boost Container"

    // TODO: Find position of "Container" using find()

    // TODO: Replace "Container" with "String" using replace()

    // TODO: Print the result

    // TODO: Append " is great!" and print again

    std::cout << "Challenge 9.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_boost_container() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 9: Boost Container\n";
    std::cout << "========================================\n";

    example_flat_map();
    challenge_flat_map();

    example_flat_set();
    challenge_flat_set();

    example_stable_vector();
    challenge_stable_vector();

    example_static_vector();
    challenge_static_vector();

    example_small_vector();
    challenge_small_vector();

    example_boost_string();
    challenge_boost_string();

    std::cout << "\n========================================\n";
    std::cout << "Boost Container exercise complete!\n";
    std::cout << "========================================\n";
}
