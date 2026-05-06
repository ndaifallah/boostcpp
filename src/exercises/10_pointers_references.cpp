#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

// ============================================================
// EXERCISE 10: Pointers and References
// ============================================================

// CONCEPT: Raw Pointers and Address-of Operator
// - &variable gives the memory address
// - *pointer dereferences to access the value
// - nullptr is the preferred null pointer constant (C++11+)
// - Pointer arithmetic works with contiguous memory

void example_raw_pointers() {
    std::cout << "\n=== Raw Pointers ===\n";

    int value = 42;
    int* ptr = &value;

    std::cout << "value = " << value << "\n";
    std::cout << "&value (address) = " << &value << "\n";
    std::cout << "ptr = " << ptr << "\n";
    std::cout << "*ptr = " << *ptr << "\n";

    *ptr = 100;
    std::cout << "After *ptr = 100: value = " << value << "\n";

    int* nullPtr = nullptr;
    std::cout << "nullptr check: " << (nullPtr == nullptr ? "null" : "valid") << "\n";
}

// CHALLENGE 10.1: Create two integers a=10, b=20.
// Create pointers pa and pb pointing to them.
// Swap the values using only the pointers (not direct variable access).
// Print the results.
void challenge_raw_pointers() {
    std::cout << "\n--- Challenge 10.1: Swap using pointers ---\n";

    // TODO: Create int a=10, b=20

    // TODO: Create pointers pa=&a, pb=&b

    // TODO: Swap the VALUES (not the pointers) using only *pa and *pb

    // TODO: Print a and b to verify they swapped

    std::cout << "Challenge 10.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: References (lvalue references)
// - Alias to an existing variable, cannot be null or reassigned
// - Passed by reference avoids copying
// - Used for output parameters and efficient function arguments
// - const& is the standard way to pass read-only arguments

void example_references() {
    std::cout << "\n=== References ===\n";

    int original = 50;
    int& ref = original;

    std::cout << "original = " << original << "\n";
    std::cout << "ref = " << ref << "\n";
    std::cout << "&original = " << &original << "\n";
    std::cout << "&ref = " << &ref << " (same address)\n";

    ref = 75;
    std::cout << "After ref = 75: original = " << original << "\n";

    auto modifyInPlace = [](int& x) { x *= 2; };
    modifyInPlace(original);
    std::cout << "After modifyInPlace: original = " << original << "\n";

    std::vector<int> large = {1, 2, 3, 4, 5};
    auto printConstRef = [](const std::vector<int>& v) {
        std::cout << "  const& size: " << v.size() << " (no copy made)\n";
    };
    std::cout << "Passing vector by const reference:\n";
    printConstRef(large);
}

// CHALLENGE 10.2: Write a function (lambda) swapRefs that takes two int&
// parameters and swaps their values. Test it with x=100, y=200.
// Also write a function printPair that takes two const int& and prints them.
void challenge_references() {
    std::cout << "\n--- Challenge 10.2: Reference-based swap ---\n";

    // TODO: Define a lambda swapRefs that takes two int& and swaps their values

    // TODO: Define a lambda printPair that takes two const int& and prints them

    // TODO: Create x=100, y=200, print them, swap, print again

    std::cout << "Challenge 10.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Pointer vs Reference semantics
// - Pointers can be reassigned, references cannot
// - Pointers can be null, references cannot
// - References are syntactically cleaner
// - Use references by default, pointers when null/reassignment needed

void example_pointer_vs_reference() {
    std::cout << "\n=== Pointer vs Reference ===\n";

    int a = 1, b = 2, c = 3;

    int* ptr = &a;
    int& ref = a;

    std::cout << "Initial: ptr->" << *ptr << ", ref->" << ref << "\n";

    ptr = &b;
    std::cout << "After ptr=&b: ptr->" << *ptr << ", ref->" << ref << "\n";

    // ref = b; // This does NOT reassign ref; it assigns b's value to a!
    ref = b;
    std::cout << "After ref=b (assigns value): ptr->" << *ptr
              << ", ref->" << ref << ", a=" << a << "\n";

    ref = c;
    std::cout << "After ref=c (assigns value): ref->" << ref << ", a=" << a << "\n";

    std::cout << "Key: ref ALWAYS refers to 'a'. Assignment changes 'a', not the binding.\n";
}

// CHALLENGE 10.3: Demonstrate pointer reassignment vs reference behavior.
// Create three ints: x=10, y=20, z=30.
// Create int* p = &x and int& r = x.
// Reassign p to point to y. Show *p and r values.
// Then set *p = 99. Show x, y, z, *p, and r values.
void challenge_pointer_vs_reference() {
    std::cout << "\n--- Challenge 10.3: Pointer reassignment demo ---\n";

    // TODO: Create int x=10, y=20, z=30

    // TODO: Create int* p = &x and int& r = x

    // TODO: Reassign p = &y

    // TODO: Print *p and r (they should differ now)

    // TODO: Set *p = 99

    // TODO: Print x, y, z, *p, r and explain what changed

    std::cout << "Challenge 10.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Rvalue References and Move Semantics
// - && binds to temporary (rvalue) objects
// - std::move() casts lvalues to rvalues
// - Enables transferring resources without copying
// - Move constructors/assignment steal resources

void example_rvalue_references() {
    std::cout << "\n=== Rvalue References ===\n";

    std::string str = "Hello";
    std::cout << "str = \"" << str << "\"\n";

    std::string lref = str;
    std::cout << "Copied to lref: \"" << lref << "\" (str still valid)\n";

    std::string rref = std::move(str);
    std::cout << "Moved to rref: \"" << rref << "\"\n";
    std::cout << "After move, str = \"" << str << "\" (valid but unspecified)\n";

    auto getValue = []() { return std::string("Temporary"); };
    std::string temp = getValue();
    std::cout << "Returned temporary: \"" << temp << "\"\n";
}

// CHALLENGE 10.4: Create a simple struct Resource { int* data; size_t size; }
// with a constructor that allocates and a destructor that frees.
// Add a move constructor that transfers ownership.
// Demonstrate move semantics with std::move.
void challenge_rvalue_references() {
    std::cout << "\n--- Challenge 10.4: Move semantics with Resource ---\n";

    // TODO: Define struct Resource with int* data, size_t size

    // TODO: Add constructor that allocates and fills data

    // TODO: Add destructor that deletes[] data

    // TODO: Add move constructor that transfers ownership (set src data to nullptr)

    // TODO: Create Resource r1(5), print its values

    // TODO: Move r1 into r2 using std::move

    // TODO: Print r2 values and verify r1 is in moved-from state

    std::cout << "Challenge 10.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Pointers to Pointers and Multi-level Indirection
// - int** is a pointer to a pointer
// - Used for dynamically allocated 2D arrays
// - C-style string arrays use const char**
// - Modern C++ prefers vector<vector<T>> or flat arrays

void example_pointer_to_pointer() {
    std::cout << "\n=== Pointer to Pointer ===\n";

    int value = 42;
    int* ptr = &value;
    int** pptr = &ptr;

    std::cout << "value = " << value << "\n";
    std::cout << "*ptr = " << *ptr << "\n";
    std::cout << "**pptr = " << **pptr << "\n";

    **pptr = 99;
    std::cout << "After **pptr = 99: value = " << value << "\n";

    const char* names[] = {"Alice", "Bob", "Charlie"};
    const char** pNames = names;

    std::cout << "C-style string array:\n";
    for (int i = 0; i < 3; ++i) {
        std::cout << "  " << pNames[i] << "\n";
    }
}

// CHALLENGE 10.5: Create a 2D array using double pointers.
// Allocate int** for 3 rows. For each row, allocate 4 ints.
// Fill with values row*10 + col.
// Print the matrix, then free all memory.
void challenge_pointer_to_pointer() {
    std::cout << "\n--- Challenge 10.5: 2D array with double pointers ---\n";

    // TODO: Allocate int** array with 3 rows (new int*[3])

    // TODO: For each row, allocate 4 ints (new int[4])

    // TODO: Fill array[row][col] = row*10 + col

    // TODO: Print the 3x4 matrix

    // TODO: Free all memory (delete[] each row, then delete[] array)

    std::cout << "Challenge 10.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: this Pointer and Member Function Pointers
// - Every non-static member function has an implicit 'this' pointer
// - Returning *this enables method chaining
// - Member function pointers have special syntax

void example_this_pointer() {
    std::cout << "\n=== this Pointer and Method Chaining ===\n";

    class Builder {
    public:
        Builder& setName(const std::string& n) {
            name_ = n;
            std::cout << "  setName(\"" << n << "\") at this=" << this << "\n";
            return *this;
        }
        Builder& setAge(int a) {
            age_ = a;
            std::cout << "  setAge(" << a << ") at this=" << this << "\n";
            return *this;
        }
        void describe() const {
            std::cout << "  " << name_ << ", age " << age_ << "\n";
        }
    private:
        std::string name_;
        int age_ = 0;
    };

    Builder b;
    b.setName("Alice").setAge(30);
    b.describe();
}

// CHALLENGE 10.6: Create a class Calculator with an int value_ member.
// Implement add(int), multiply(int), subtract(int) that modify value_
// and return *this for chaining.
// Start with 0, chain: .add(5).multiply(3).subtract(4) and print result (should be 11).
void challenge_this_pointer() {
    std::cout << "\n--- Challenge 10.6: Method chaining calculator ---\n";

    // TODO: Define class Calculator with int value_ = 0

    // TODO: Implement add(int), multiply(int), subtract(int) returning Calculator&

    // TODO: Chain: Calculator().add(5).multiply(3).subtract(4)

    // TODO: Print the final result (should be 11)

    std::cout << "Challenge 10.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_pointers_references() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 10: Pointers and References\n";
    std::cout << "========================================\n";

    example_raw_pointers();
    challenge_raw_pointers();

    example_references();
    challenge_references();

    example_pointer_vs_reference();
    challenge_pointer_vs_reference();

    example_rvalue_references();
    challenge_rvalue_references();

    example_pointer_to_pointer();
    challenge_pointer_to_pointer();

    example_this_pointer();
    challenge_this_pointer();

    std::cout << "\n========================================\n";
    std::cout << "Pointers and References exercise complete!\n";
    std::cout << "========================================\n";
}
