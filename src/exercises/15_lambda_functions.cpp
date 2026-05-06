#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

// ============================================================
// EXERCISE 15: Lambda Functions
// ============================================================

// CONCEPT: Basic Lambda Syntax
// - Syntax: [capture](params) -> return_type { body }
// - Capture list: what external variables to access
// - Return type can be omitted (deduced by compiler)
// - Can be used inline or stored in variables

void example_lambda_basic() {
    std::cout << "\n=== Basic Lambda Syntax ===\n";

    // Simple lambda with no capture, no parameters
    auto greet = []() { std::cout << "Hello from lambda!\n"; };
    greet();

    // Lambda with parameters and return value
    auto add = [](int a, int b) { return a + b; };
    std::cout << "add(3, 4) = " << add(3, 4) << "\n";

    // Lambda used inline with STL
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::cout << "Numbers: ";
    std::for_each(nums.begin(), nums.end(), [](int n) { std::cout << n << " "; });
    std::cout << "\n";

    // Explicit return type
    auto divide = [](double a, double b) -> double {
        if (b == 0) return 0.0;
        return a / b;
    };
    std::cout << "divide(10, 3) = " << divide(10, 3) << "\n";
}

// CHALLENGE 15.1: Write a lambda that takes two strings and returns their
// concatenated result. Test it with "Hello, " and "World!".
void challenge_lambda_basic() {
    std::cout << "\n--- Challenge 15.1: String concatenation lambda ---\n";

    // TODO: Define auto concat = [](const std::string& a, const std::string& b) { ... };

    // TODO: Call concat("Hello, ", "World!") and print the result

    std::cout << "Challenge 15.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Lambda Capture Clauses
// - [] : capture nothing
// - [x] : capture x by value (copy)
// - [&x] : capture x by reference
// - [=] : capture all external variables by value
// - [&] : capture all external variables by reference
// - [this] : capture current object pointer (in class methods)

void example_lambda_capture() {
    std::cout << "\n=== Lambda Capture ===\n";

    int a = 10, b = 20;

    // Capture by value
    auto captureValue = [a, b]() { std::cout << "Captured by value: a=" << a << ", b=" << b << "\n"; };
    captureValue();

    // Capture by reference
    auto captureRef = [&a, &b]() {
        a *= 2;
        b *= 2;
        std::cout << "Captured by reference: a=" << a << ", b=" << b << "\n";
    };
    captureRef();
    std::cout << "After captureRef: a=" << a << ", b=" << b << "\n";

    // Capture all by value
    int c = 30;
    auto captureAllValue = [=]() { std::cout << "Captured all by value: a=" << a << ", c=" << c << "\n"; };
    captureAllValue();

    // Capture all by reference
    auto captureAllRef = [&]() {
        a = 1;
        b = 2;
        c = 3;
        std::cout << "Captured all by reference: a=" << a << ", b=" << b << ", c=" << c << "\n";
    };
    captureAllRef();
}

// CHALLENGE 15.2: Create a vector<int> and a lambda that captures it by
// reference, then adds 5 to each element using for_each.
void challenge_lambda_capture() {
    std::cout << "\n--- Challenge 15.2: Modify vector via lambda capture ---\n";

    // TODO: Create vector<int> v = {1, 2, 3, 4, 5};

    // TODO: Define lambda that captures v by reference and adds 5 to each element

    // TODO: Use std::for_each with the lambda

    // TODO: Print the modified vector

    std::cout << "Challenge 15.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Mutable Lambdas
// - By default, value-captured variables are const inside lambda
// - Use 'mutable' keyword to modify value-captured copies
// - Does not affect the original external variable

void example_lambda_mutable() {
    std::cout << "\n=== Mutable Lambdas ===\n";

    int counter = 0;

    // Non-mutable: can't modify value-captured variable
    // auto inc = [counter]() { counter++; }; // ERROR

    // Mutable: can modify the copy
    auto mutableInc = [counter]() mutable {
        counter++;
        std::cout << "Inside mutable lambda: counter=" << counter << "\n";
    };

    mutableInc();
    mutableInc();
    std::cout << "Original counter after mutable lambda calls: " << counter << " (unchanged)\n";
}

// CHALLENGE 15.3: Create a mutable lambda that acts as a running total
// accumulator. Each call adds the input to an internal sum.
void challenge_lambda_mutable() {
    std::cout << "\n--- Challenge 15.3: Mutable accumulator lambda ---\n";

    // TODO: Define auto accumulator = [sum = 0](int x) mutable { ... };

    // TODO: Call accumulator(5), accumulator(10), accumulator(15)

    // TODO: Print the running total after each call

    std::cout << "Challenge 15.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Generic Lambdas (C++14+)
// - Use 'auto' in parameters for type deduction
// - Equivalent to a template function
// - Works with any type that supports the operations used

void example_lambda_generic() {
    std::cout << "\n=== Generic Lambdas ===\n";

    // Generic lambda: works with any type supporting +
    auto genericAdd = [](auto a, auto b) { return a + b; };

    std::cout << "genericAdd(3, 4) = " << genericAdd(3, 4) << "\n";
    std::cout << "genericAdd(3.5, 4.5) = " << genericAdd(3.5, 4.5) << "\n";
    std::cout << "genericAdd(std::string(\"a\"), \"b\") = " << genericAdd(std::string("a"), "b") << "\n";

    // Use with STL transform
    std::vector<int> nums = {1, 2, 3, 4};
    std::vector<int> doubled(nums.size());
    std::transform(nums.begin(), nums.end(), doubled.begin(),
                   [](auto n) { return n * 2; });
    std::cout << "Doubled: ";
    for (int n : doubled) std::cout << n << " ";
    std::cout << "\n";
}

// CHALLENGE 15.4: Write a generic lambda that returns the larger of two
// values. Test it with int, double, and string types.
void challenge_lambda_generic() {
    std::cout << "\n--- Challenge 15.4: Generic max lambda ---\n";

    // TODO: Define auto genericMax = [](auto a, auto b) { ... };

    // TODO: Test with int: 10, 20

    // TODO: Test with double: 3.14, 2.71

    // TODO: Test with string: "apple", "banana"

    std::cout << "Challenge 15.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Lambdas as Arguments and Return Values
// - Pass lambdas to functions (e.g., STL algorithms)
// - Store lambdas in std::function for later use
// - Return lambdas from functions (factory pattern)

void example_lambda_higher_order() {
    std::cout << "\n=== Lambdas as Arguments/Returns ===\n";

    // Lambda as argument to a function
    auto applyOperation = [](int x, int y, auto op) { return op(x, y); };
    auto multiply = [](int a, int b) { return a * b; };
    std::cout << "applyOperation(5, 6, multiply) = " << applyOperation(5, 6, multiply) << "\n";

    // Store in std::function
    std::function<int(int, int)> storedLambda = [](int a, int b) { return a - b; };
    std::cout << "storedLambda(10, 3) = " << storedLambda(10, 3) << "\n";

    // Return lambda from function (factory)
    auto makeMultiplier = [](int factor) {
        return [factor](int x) { return x * factor; };
    };
    auto triple = makeMultiplier(3);
    std::cout << "triple(7) = " << triple(7) << "\n";
}

// CHALLENGE 15.5: Create a function that takes a vector and a lambda,
// and returns a new vector with elements filtered by the lambda predicate.
void challenge_lambda_filter() {
    std::cout << "\n--- Challenge 15.5: Filter vector with lambda ---\n";

    // TODO: Define auto filter = [](const std::vector<int>& v, auto pred) -> std::vector<int> { ... };

    // TODO: Filter even numbers from {1,2,3,4,5,6}

    // TODO: Filter numbers greater than 3

    std::cout << "Challenge 15.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Immediately Invoked Lambda (IILE)
// - Define and call a lambda immediately
// - Useful for one-time initialization, limiting scope
// - Can return a value for initialization

void example_lambda_iile() {
    std::cout << "\n=== Immediately Invoked Lambda ===\n";

    // Initialize a complex value with an IIFE
    int result = [](int x) {
        std::cout << "  Computing in IIFE with x=" << x << "\n";
        return x * x + 2 * x + 1;
    }(5);  // Called immediately with argument 5

    std::cout << "IILE result: " << result << "\n";

    // Scope limiting: variables inside lambda don't leak
    {
        []() {
            int temp = 42;
            std::cout << "  Temp inside IIFE: " << temp << "\n";
        }();  // Called immediately, no assignment needed
        // temp is not accessible here
    }
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_lambda_functions() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 15: Lambda Functions\n";
    std::cout << "========================================\n";

    example_lambda_basic();
    challenge_lambda_basic();

    example_lambda_capture();
    challenge_lambda_capture();

    example_lambda_mutable();
    challenge_lambda_mutable();

    example_lambda_generic();
    challenge_lambda_generic();

    example_lambda_higher_order();
    challenge_lambda_filter();

    example_lambda_iile();

    std::cout << "\n========================================\n";
    std::cout << "Lambda Functions exercise complete!\n";
    std::cout << "========================================\n";
}
