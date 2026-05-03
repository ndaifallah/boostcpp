#include <iostream>
#include <optional>
#include <variant>
#include <any>
#include <string>
#include <string_view>
#include <vector>
#include <map>
#include <filesystem>

// ============================================================
// EXERCISE 3: C++17 Additions
// ============================================================

// CONCEPT: std::optional
// - Represents a value that may or may not exist
// - Safer alternative to returning pointers or sentinel values
// - Replaces patterns like returning -1 or nullptr for "not found"

void example_optional() {
    std::cout << "\n=== std::optional Examples ===\n";

    // Function that might not return a value
    auto safe_divide = [](double a, double b) -> std::optional<double> {
        if (b == 0) return std::nullopt;
        return a / b;
    };

    if (auto result = safe_divide(10, 3)) {
        std::cout << "10 / 3 = " << *result << "\n";
    }

    if (auto result = safe_divide(10, 0)) {
        std::cout << "This won't print\n";
    } else {
        std::cout << "Division by zero detected!\n";
    }

    // Or use value_or for default
    std::optional<int> maybe_value;
    std::cout << "Default: " << maybe_value.value_or(42) << "\n";
}

// CHALLENGE 3.1: Use optional for safe lookups
void challenge_optional() {
    std::cout << "\n--- Challenge 3.1: Optional safe lookups ---\n";

    std::map<std::string, int> ages = {
        {"Alice", 30}, {"Bob", 25}, {"Charlie", 35}
    };

    // TODO: Write a function (or lambda) that takes a name and returns
    //       std::optional<int> - the age if found, std::nullopt if not

    // TODO: Test with "Bob" (should find age)

    // TODO: Test with "David" (should not find)

    // TODO: Use value_or(0) to provide a default age for unknown people

    std::cout << "Challenge 3.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::variant
// - Type-safe union - holds one of several specified types
// - Use std::get<T> or std::visit to access the value
// - std::holds_alternative<T> to check which type is active

void example_variant() {
    std::cout << "\n=== std::variant Examples ===\n";

    std::variant<int, std::string, double> value;

    value = 42;
    std::cout << "Holds int: " << std::holds_alternative<int>(value) << "\n";
    std::cout << "Value: " << std::get<int>(value) << "\n";

    value = std::string("Hello");
    std::cout << "Holds string: " << std::holds_alternative<std::string>(value) << "\n";

    // Safe access with std::visit
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>)
            std::cout << "int: " << arg << "\n";
        else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "string: " << arg << "\n";
        else if constexpr (std::is_same_v<T, double>)
            std::cout << "double: " << arg << "\n";
    }, value);

    std::cout << "Active index: " << value.index() << "\n";
}

// CHALLENGE 3.2: Create a variant-based JSON-like value type
void challenge_variant() {
    std::cout << "\n--- Challenge 3.2: Variant value type ---\n";

    // TODO: Define a variant that can hold int, double, bool, or string
    // using JsonValue = std::variant<int, double, bool, std::string>;

    // TODO: Create a vector of JsonValue with different types

    // TODO: Use std::visit to print each value with its type label

    // TODO: (Bonus) Write a function that converts JsonValue to string
    //       using std::visit

    std::cout << "Challenge 3.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::any
// - Holds any copy-constructible type
// - Use std::any_cast<T> to retrieve the value (throws if wrong type)
// - Use any.type() to inspect the type

void example_any() {
    std::cout << "\n=== std::any Examples ===\n";

    std::any container;

    container = 42;
    std::cout << "Has value: " << container.has_value() << "\n";
    std::cout << "Type info: " << container.type().name() << "\n";

    if (container.type() == typeid(int)) {
        std::cout << "Stored int: " << std::any_cast<int>(container) << "\n";
    }

    container = std::string("Hello");
    std::cout << "Stored string: " << std::any_cast<std::string>(container) << "\n";

    container.reset();
    std::cout << "After reset, has value: " << container.has_value() << "\n";
}

// CHALLENGE 3.3: Use std::any as a heterogeneous container
void challenge_any() {
    std::cout << "\n--- Challenge 3.3: Any heterogeneous container ---\n";

    // TODO: Create a vector<std::any> containing an int, a string, and a double

    // TODO: Iterate and print each value with its type
    // Hint: Compare .type() with typeid(int), typeid(string), etc.

    // TODO: (Bonus) Try casting to the wrong type and catch std::bad_any_cast

    std::cout << "Challenge 3.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::string_view
// - Non-owning reference to a string
// - Zero-copy, efficient string passing
// - Don't use with temporary strings!

void example_string_view() {
    std::cout << "\n=== std::string_view Examples ===\n";

    std::string str = "Hello, World!";
    std::string_view sv(str); // No copy!

    std::cout << "string_view: " << sv << "\n";
    std::cout << "Length: " << sv.length() << "\n";

    // Works with string literals directly
    std::string_view literal_sv = "This is efficient!";

    // Substring views (no allocation)
    std::string_view sub = sv.substr(7, 5);
    std::cout << "Substring: " << sub << "\n"; // "World"

    // Efficient function parameter
    auto count_vowels = [](std::string_view s) {
        int count = 0;
        for (char c : s) {
            char lower = std::tolower(c);
            if (lower == 'a' || lower == 'e' || lower == 'i' ||
                lower == 'o' || lower == 'u') {
                count++;
            }
        }
        return count;
    };

    std::cout << "Vowels in str: " << count_vowels(str) << "\n";
    std::cout << "Vowels in literal: " << count_vowels("aeiou") << "\n";
}

// CHALLENGE 3.4: Use string_view for string processing
void challenge_string_view() {
    std::cout << "\n--- Challenge 3.4: String processing with string_view ---\n";

    std::string text = "The quick brown fox jumps over the lazy dog";

    // TODO: Write a function that takes string_view and returns the first word
    // Hint: Find first space with find(' '), then substr(0, pos)

    // TODO: Write a function that takes string_view and checks if it
    //       starts with a given prefix
    // Hint: sv.starts_with(prefix) - C++20, or sv.substr(0, prefix.size()) == prefix

    // TODO: Write a function that trims whitespace from both ends
    //       using string_view (no copy!)

    std::cout << "Challenge 3.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Structured Bindings
// - Unpack tuples, pairs, structs into named variables
// - Cleaner than using .first, .second, or get<0>()

void example_structured_bindings() {
    std::cout << "\n=== Structured Bindings Examples ===\n";

    // Pairs
    std::pair<int, std::string> p = {1, "Alice"};
    auto [id, name] = p;
    std::cout << "ID: " << id << ", Name: " << name << "\n";

    // Map iteration
    std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};
    for (const auto& [student, score] : scores) {
        std::cout << student << ": " << score << "\n";
    }

    // Struct
    struct Point3D { int x, y, z; };
    Point3D point{10, 20, 30};
    auto [x, y, z] = point;
    std::cout << "Point: (" << x << ", " << y << ", " << z << ")\n";

    // Tie with tuple (pre-C++17 style for comparison)
    auto result = std::make_tuple(1, 2.0, "three");
    auto [a, b, c] = result;
    std::cout << "Tuple: " << a << ", " << b << ", " << c << "\n";
}

// CHALLENGE 3.5: Use structured bindings for cleaner code
void challenge_structured_bindings() {
    std::cout << "\n--- Challenge 3.5: Structured bindings ---\n";

    std::map<std::string, std::pair<int, double>> data = {
        {"Alice", {25, 3.8}},
        {"Bob", {30, 3.5}},
        {"Charlie", {22, 3.9}}
    };

    // TODO: Iterate over the map and print each entry using structured bindings
    //       to unpack the name, age, and gpa
    // Expected output: "Alice is 25 years old with GPA 3.8"

    // TODO: Write a function that returns a tuple {name, age, city}
    //       and use structured bindings to receive it

    std::cout << "Challenge 3.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: if constexpr (C++17)
// - Compile-time conditional in templates
// - Discarded branch is not instantiated

void example_if_constexpr() {
    std::cout << "\n=== if constexpr Examples ===\n";

    auto describe = [](auto&& value) {
        using T = std::decay_t<decltype(value)>;
        if constexpr (std::is_integral_v<T>) {
            std::cout << "Integral: " << value << "\n";
        } else if constexpr (std::is_floating_point_v<T>) {
            std::cout << "Floating: " << value << "\n";
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "String: " << value << "\n";
        } else {
            std::cout << "Other type\n";
        }
    };

    describe(42);
    describe(3.14);
    describe(std::string("Hello"));
}

// CHALLENGE 3.6: Use if constexpr for type-based processing
void challenge_if_constexpr() {
    std::cout << "\n--- Challenge 3.6: if constexpr ---\n";

    // TODO: Write a template function to_string_custom(T&& value)
    //       that uses if constexpr to convert different types to string:
    //       - int: wrap in brackets like "[42]"
    //       - double: round to 2 decimal places
    //       - string: wrap in quotes like ""hello""
    //       - other: just use std::to_string or stream

    // TODO: Test with int, double, and string

    std::cout << "Challenge 3.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::filesystem (C++17)
// - Cross-platform file system operations
// - Paths, directory iteration, file status

void example_filesystem() {
    std::cout << "\n=== std::filesystem Examples ===\n";

    namespace fs = std::filesystem;

    // Current path
    std::cout << "Current path: " << fs::current_path() << "\n";

    // Path operations
    fs::path p = "/Users/example/file.txt";
    std::cout << "Filename: " << p.filename() << "\n";
    std::cout << "Extension: " << p.extension() << "\n";
    std::cout << "Stem: " << p.stem() << "\n";
    std::cout << "Parent: " << p.parent_path() << "\n";

    // Check if path exists
    std::cout << "Path exists: " << fs::exists(p) << "\n";

    // List directory contents (if directory exists)
    auto cwd = fs::current_path();
    std::cout << "Contents of current directory:\n";
    for (const auto& entry : fs::directory_iterator(cwd)) {
        std::cout << "  " << (entry.is_directory() ? "[D] " : "[F] ")
                  << entry.path().filename() << "\n";
    }
}

// CHALLENGE 3.7: Use filesystem for file operations
void challenge_filesystem() {
    std::cout << "\n--- Challenge 3.7: Filesystem operations ---\n";

    namespace fs = std::filesystem;

    // TODO: List all .cpp files in the current project directory
    // Hint: Use directory_iterator and check extension

    // TODO: Count the number of files vs directories in src/

    // TODO: (Bonus) Find the largest file in the current directory
    // Hint: fs::file_size()

    std::cout << "Challenge 3.7 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_cpp17_additions() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 3: C++17 Additions\n";
    std::cout << "========================================\n";

    example_optional();
    challenge_optional();

    example_variant();
    challenge_variant();

    example_any();
    challenge_any();

    example_string_view();
    challenge_string_view();

    example_structured_bindings();
    challenge_structured_bindings();

    example_if_constexpr();
    challenge_if_constexpr();

    example_filesystem();
    challenge_filesystem();

    std::cout << "\n========================================\n";
    std::cout << "C++17 Additions exercise complete!\n";
    std::cout << "========================================\n";
}
