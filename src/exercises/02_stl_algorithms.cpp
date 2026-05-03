#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iterator>
#include <map>

// ============================================================
// EXERCISE 2: STL Algorithms
// ============================================================

// CONCEPT: Searching and Finding
// std::find, std::find_if, std::binary_search

void example_finding() {
    std::cout << "\n=== Finding Elements ===\n";

    std::vector<int> nums = {3, 7, 1, 9, 4, 7, 2};

    // Find a specific value
    auto it = std::find(nums.begin(), nums.end(), 9);
    if (it != nums.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    // Find with condition (lambda)
    auto even = std::find_if(nums.begin(), nums.end(), [](int n) {
        return n % 2 == 0;
    });
    if (even != nums.end()) {
        std::cout << "First even: " << *even << "\n";
    }

    // Find all occurrences
    std::cout << "All 7s at indices: ";
    auto start = nums.begin();
    while ((start = std::find(start, nums.end(), 7)) != nums.end()) {
        std::cout << (start - nums.begin()) << " ";
        ++start;
    }
    std::cout << "\n";
}

// CHALLENGE 2.1: Find elements with conditions
void challenge_finding() {
    std::cout << "\n--- Challenge 2.1: Find with conditions ---\n";

    std::vector<std::string> words = {"apple", "banana", "avocado", "cherry", "apricot"};

    // TODO: Find the first word that starts with 'a'
    // Hint: Use find_if with a lambda that checks word.front() == 'a'

    // TODO: Find the first word with length > 5

    // TODO: Count how many words contain the letter 'r'
    // Hint: Use std::count_if

    std::cout << "Challenge 2.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Transforming data
// std::transform, std::for_each

void example_transforming() {
    std::cout << "\n=== Transforming Data ===\n";

    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Square each element (in-place)
    std::transform(nums.begin(), nums.end(), nums.begin(), [](int n) {
        return n * n;
    });

    std::cout << "Squared: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Transform to different type
    std::vector<std::string> words = {"hello", "world"};
    std::vector<size_t> lengths;
    lengths.resize(words.size());
    std::transform(words.begin(), words.end(), lengths.begin(),
                   [](const std::string& s) { return s.size(); });

    std::cout << "Lengths: ";
    for (auto l : lengths) std::cout << l << " ";
    std::cout << "\n";
}

// CHALLENGE 2.2: Transform a vector of strings to uppercase
void challenge_transforming() {
    std::cout << "\n--- Challenge 2.2: String transformations ---\n";

    std::vector<std::string> words = {"hello", "world", "cpp", "boost"};

    // TODO: Transform all words to uppercase
    // Hint: std::transform with std::toupper, note toupper works on char
    //       so you need nested transform or a helper lambda

    // TODO: Transform words into a vector of their lengths

    // TODO: Create a new vector containing only the word lengths squared
    //       (combine the two steps above)

    std::cout << "Challenge 2.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Accumulating and Reducing
// std::accumulate, std::reduce (C++17)

void example_accumulating() {
    std::cout << "\n=== Accumulating ===\n";

    std::vector<int> nums = {1, 2, 3, 4, 5};

    // Sum
    int sum = std::accumulate(nums.begin(), nums.end(), 0);
    std::cout << "Sum: " << sum << "\n";

    // Product
    int product = std::accumulate(nums.begin(), nums.end(), 1,
                                  std::multiplies<int>());
    std::cout << "Product: " << product << "\n";

    // Build a string
    std::vector<std::string> words = {"C", "++", " is", " fun"};
    std::string sentence = std::accumulate(
        words.begin(), words.end(), std::string{},
        [](const std::string& a, const std::string& b) { return a + b; });
    std::cout << sentence << "\n";
}

// CHALLENGE 2.3: Use accumulate for custom reductions
void challenge_accumulating() {
    std::cout << "\n--- Challenge 2.3: Custom accumulation ---\n";

    std::vector<int> nums = {10, 20, 30, 40, 50};

    // TODO: Find the maximum element using accumulate
    // Hint: std::accumulate with a lambda that returns std::max(a, b)

    // TODO: Calculate the average (sum / count)

    // TODO: Count how many numbers are greater than 25
    // Hint: accumulate starting from 0, add 1 if element > 25

    // TODO (C++17): Try std::reduce instead of accumulate
    // Hint: std::reduce(nums.begin(), nums.end(), 0) - similar but parallelizable

    std::cout << "Challenge 2.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Sorting and Partitioning
// std::sort, std::stable_sort, std::partition

void example_sorting() {
    std::cout << "\n=== Sorting and Partitioning ===\n";

    std::vector<int> nums = {5, 3, 8, 1, 9, 2, 7};

    // Default sort (ascending)
    std::sort(nums.begin(), nums.end());
    std::cout << "Sorted ascending: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Custom comparator (descending)
    std::sort(nums.begin(), nums.end(), std::greater<int>());
    std::cout << "Sorted descending: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Partition: move evens to front
    nums = {5, 3, 8, 1, 9, 2, 7};
    auto pivot = std::partition(nums.begin(), nums.end(), [](int n) {
        return n % 2 == 0;
    });
    std::cout << "Evens first: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << " (pivot at index " << (pivot - nums.begin()) << ")\n";
}

// CHALLENGE 2.4: Sort and partition custom data
void challenge_sorting() {
    std::cout << "\n--- Challenge 2.4: Custom sorting ---\n";

    std::vector<std::pair<std::string, int>> scores = {
        {"Alice", 85}, {"Bob", 92}, {"Charlie", 78},
        {"Diana", 92}, {"Eve", 88}
    };

    // TODO: Sort by score (highest first)
    // Hint: Lambda comparing .second values

    // TODO: Print the sorted results

    // TODO: If scores are equal, sort alphabetically by name
    // Hint: Compare .second first, if equal compare .first

    // TODO: Partition the vector to put scores >= 90 at the front

    std::cout << "Challenge 2.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Modifying sequences
// std::copy, std::remove_if, std::unique, std::reverse

void example_modifying() {
    std::cout << "\n=== Modifying Sequences ===\n";

    // Remove-erase idiom (very important!)
    std::vector<int> nums = {1, 2, 3, 2, 4, 2, 5};
    nums.erase(std::remove(nums.begin(), nums.end(), 2), nums.end());

    std::cout << "After removing 2s: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Remove duplicates (requires sorted range)
    std::vector<int> dupes = {1, 2, 2, 3, 3, 3, 4};
    auto last = std::unique(dupes.begin(), dupes.end());
    dupes.erase(last, dupes.end());

    std::cout << "After unique: ";
    for (int n : dupes) std::cout << n << " ";
    std::cout << "\n";

    // Copy with back_inserter
    std::vector<int> src = {10, 20, 30};
    std::vector<int> dst = {1, 2, 3};
    std::copy(src.begin(), src.end(), std::back_inserter(dst));

    std::cout << "After copy: ";
    for (int n : dst) std::cout << n << " ";
    std::cout << "\n";
}

// CHALLENGE 2.5: Remove elements and manipulate sequences
void challenge_modifying() {
    std::cout << "\n--- Challenge 2.5: Sequence manipulation ---\n";

    std::vector<std::string> words = {"apple", "", "banana", "", "cherry", ""};

    // TODO: Remove all empty strings using remove-erase idiom

    // TODO: Sort the remaining words alphabetically

    // TODO: Remove duplicate words (if any exist)

    // TODO: Reverse the vector in place

    std::cout << "Challenge 2.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Numeric algorithms
// std::iota, std::inner_product (C++17: std::gcd, std::lcm)

void example_numeric() {
    std::cout << "\n=== Numeric Algorithms ===\n";

    // Fill with sequential values
    std::vector<int> nums(10);
    std::iota(nums.begin(), nums.end(), 1); // 1, 2, 3, ..., 10

    std::cout << "iota 1-10: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Inner product (dot product)
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "Dot product: " << dot << "\n"; // 1*4 + 2*5 + 3*6 = 32

    // C++17: gcd and lcm
    std::cout << "gcd(12, 8) = " << std::gcd(12, 8) << "\n";
    std::cout << "lcm(12, 8) = " << std::lcm(12, 8) << "\n";
}

// CHALLENGE 2.6: Use numeric algorithms
void challenge_numeric() {
    std::cout << "\n--- Challenge 2.6: Numeric operations ---\n";

    // TODO: Create a vector of 20 integers filled with values 0-19 using iota

    // TODO: Calculate the dot product of {1, 2, 3, 4} and {5, 6, 7, 8}

    // TODO: Create a vector of 5 elements and fill with iota starting from 100

    // TODO: (Bonus) Use adjacent_difference to find differences between
    //       consecutive elements in {1, 4, 9, 16, 25}

    std::cout << "Challenge 2.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_stl_algorithms() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 2: STL Algorithms\n";
    std::cout << "========================================\n";

    example_finding();
    challenge_finding();

    example_transforming();
    challenge_transforming();

    example_accumulating();
    challenge_accumulating();

    example_sorting();
    challenge_sorting();

    example_modifying();
    challenge_modifying();

    example_numeric();
    challenge_numeric();

    std::cout << "\n========================================\n";
    std::cout << "STL Algorithms exercise complete!\n";
    std::cout << "========================================\n";
}
