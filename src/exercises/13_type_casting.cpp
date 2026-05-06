#include <iostream>
#include <string>
#include <vector>

// ============================================================
// EXERCISE 13: Static and Dynamic Type Casting
// ============================================================

// CONCEPT: static_cast
// - Compile-time type conversion with compile-time checks
// - Used for: numeric conversions, void* to typed pointer, up/down casts (non-polymorphic)
// - No runtime overhead, but no runtime safety checks
// - Preferred for explicit conversions that are known to be safe

void example_static_cast() {
    std::cout << "\n=== static_cast ===\n";

    // Numeric conversion
    double d = 3.14159;
    int i = static_cast<int>(d);
    std::cout << "double " << d << " -> int " << i << " (truncates)\n";

    // void* to typed pointer (common in memory management)
    int value = 42;
    void* vptr = &value;
    int* iptr = static_cast<int*>(vptr);
    std::cout << "void* -> int*: " << *iptr << "\n";

    // Upcast (derived to base) - always safe
    struct Base { int x = 1; };
    struct Derived : Base { int y = 2; };
    Derived der;
    Base* basePtr = static_cast<Base*>(&der);
    std::cout << "Upcast Derived->Base: x=" << basePtr->x << "\n";

    // Downcast (base to derived) - unsafe without knowing actual type
    Base base;
    Derived* derivedPtr = static_cast<Derived*>(&base);  // Compiles but dangerous!
    std::cout << "Downcast Base->Derived (unsafe): " << derivedPtr->y << " (undefined behavior)\n";
}

// CHALLENGE 13.1: Use static_cast to convert a long value to int.
// Also convert a float to double, then back to float. Print all values.
void challenge_static_cast() {
    std::cout << "\n--- Challenge 13.1: Numeric static_cast ---\n";

    // TODO: Create long l = 1234567890123L and cast to int, print both

    // TODO: Create float f = 3.14f, cast to double, then back to float, print all

    std::cout << "Challenge 13.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: dynamic_cast
// - Runtime type checking for polymorphic class hierarchies
// - Requires at least one virtual function in the base class
// - Returns nullptr for pointer casts if the object isn't of the target type
// - Throws std::bad_cast for reference casts if invalid
// - Has runtime overhead (RTTI - Run-Time Type Identification)

void example_dynamic_cast() {
    std::cout << "\n=== dynamic_cast ===\n";

    struct Base {
        virtual ~Base() {}  // Virtual destructor enables polymorphism
        virtual void speak() { std::cout << "Base\n"; }
    };

    struct Derived1 : Base {
        void speak() override { std::cout << "Derived1\n"; }
        void method1() { std::cout << "Derived1 specific method\n"; }
    };

    struct Derived2 : Base {
        void speak() override { std::cout << "Derived2\n"; }
        void method2() { std::cout << "Derived2 specific method\n"; }
    };

    // Create objects with actual derived types
    Derived1 d1;
    Derived2 d2;

    Base* b1 = &d1;  // Upcast to Base*
    Base* b2 = &d2;

    // Safe downcast using dynamic_cast
    Derived1* pd1 = dynamic_cast<Derived1*>(b1);
    if (pd1) {
        std::cout << "b1 is Derived1: ";
        pd1->method1();
    } else {
        std::cout << "b1 is NOT Derived1\n";
    }

    Derived1* pd1_from_b2 = dynamic_cast<Derived1*>(b2);
    if (pd1_from_b2) {
        std::cout << "b2 is Derived1: ";
        pd1_from_b2->method1();
    } else {
        std::cout << "b2 is NOT Derived1 (dynamic_cast returned nullptr)\n";
    }

    // Reference version - throws std::bad_cast if invalid
    try {
        Derived1& ref1 = dynamic_cast<Derived1&>(*b1);
        std::cout << "Reference cast succeeded for b1\n";
    } catch (const std::bad_cast& e) {
        std::cout << "Reference cast failed: " << e.what() << "\n";
    }
}

// CHALLENGE 13.2: Create a base class Shape with virtual area() method.
// Create Circle and Square derived classes with appropriate area calculations.
// Use dynamic_cast to safely identify which type a Shape* points to and
// call type-specific methods (e.g., getRadius() for Circle).
void challenge_dynamic_cast() {
    std::cout << "\n--- Challenge 13.2: Polymorphic hierarchy with dynamic_cast ---\n";

    // TODO: Define class Shape with virtual double area() = 0 and virtual ~Shape()

    // TODO: Define class Circle : public Shape with radius, area(), getRadius()

    // TODO: Define class Square : public Shape with side, area(), getSide()

    // TODO: Create Circle and Square objects, store as Shape*

    // TODO: Use dynamic_cast to check types and call specific methods

    std::cout << "Challenge 13.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: reinterpret_cast
// - Low-level reinterpretation of bit patterns
// - No compile-time or runtime checks
// - Implementation-defined behavior
// - Use only when absolutely necessary (e.g., low-level system programming)

void example_reinterpret_cast() {
    std::cout << "\n=== reinterpret_cast ===\n";

    int value = 0x12345678;
    // Reinterpret the int's bits as a char array
    char* bytes = reinterpret_cast<char*>(&value);

    std::cout << "int value 0x" << std::hex << value << std::dec << " as bytes: ";
    for (size_t i = 0; i < sizeof(int); ++i) {
        std::cout << std::hex << (static_cast<int>(bytes[i]) & 0xFF) << " ";
    }
    std::cout << std::dec << "\n";

    // Pointer to integer and back (implementation-defined)
    int* ptr = &value;
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    std::cout << "Pointer " << ptr << " as integer: " << addr << "\n";

    int* ptr2 = reinterpret_cast<int*>(addr);
    std::cout << "Integer back to pointer: " << ptr2 << " (should match original)\n";
}

// CHALLENGE 13.3: Use reinterpret_cast to treat an array of 4 bytes as a uint32_t.
// Set the bytes to {0x11, 0x22, 0x33, 0x44} and print the resulting uint32_t.
// Note: result is endian-dependent.
void challenge_reinterpret_cast() {
    std::cout << "\n--- Challenge 13.3: Bit pattern reinterpretation ---\n";

    // TODO: Create char bytes[4] = {0x11, 0x22, 0x33, 0x44}

    // TODO: Use reinterpret_cast to treat bytes as uint32_t*

    // TODO: Print the resulting uint32_t value (in hex)

    std::cout << "Challenge 13.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: const_cast
// - Adds or removes const/volatile qualifiers
// - Does not change the actual object, only the pointer/reference type
// - Use case: calling non-const APIs with const objects (when you know it's safe)
// - Modifying an originally const object via const_cast is undefined behavior

void example_const_cast() {
    std::cout << "\n=== const_cast ===\n";

    int mutableValue = 100;
    const int* constPtr = &mutableValue;

    // Remove const to modify through pointer (safe because original is non-const)
    int* mutablePtr = const_cast<int*>(constPtr);
    *mutablePtr = 200;
    std::cout << "After const_cast modification: " << mutableValue << "\n";

    // Use case: legacy API that doesn't respect const
    auto legacyApi = [](int* p) { *p = 999; };
    legacyApi(const_cast<int*>(constPtr));
    std::cout << "After legacy API call: " << mutableValue << "\n";

    // WARNING: Modifying an originally const object is undefined behavior
    const int immutable = 42;
    // int* bad = const_cast<int*>(&immutable);
    // *bad = 0;  // UNDEFINED BEHAVIOR!
    std::cout << "Original const object unchanged: " << immutable << "\n";
}

// CHALLENGE 13.4: Write a function that takes a const int& but needs to
// call a legacy function that takes int* (and won't modify the data).
// Use const_cast to safely bridge the gap. Demonstrate the pattern.
void challenge_const_cast() {
    std::cout << "\n--- Challenge 13.4: const_cast for API compatibility ---\n";

    // TODO: Define a legacy function: void oldFunc(int* p) { ... }

    // TODO: Define a wrapper that takes const int& and calls oldFunc safely

    // TODO: Test with a mutable int (should work)

    // TODO: Explain why calling with an originally const object would be dangerous

    std::cout << "Challenge 13.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: C-style casts and when to avoid them
// - C-style cast: (TargetType)expression
// - Can perform static_cast, reinterpret_cast, or const_cast depending on context
// - Not explicit about intent, harder to search for, no compile-time safety
// - Prefer C++ casts for clarity and safety

void example_cstyle_vs_cpp_casts() {
    std::cout << "\n=== C-style casts vs C++ casts ===\n";

    double pi = 3.14159;

    // C-style cast
    int i1 = (int)pi;
    // C++ static_cast (preferred)
    int i2 = static_cast<int>(pi);

    std::cout << "C-style: " << i1 << ", C++ static_cast: " << i2 << "\n";

    const char* str = "hello";
    // C-style: (char*)str  - removes const, but unclear intent
    // C++: const_cast<char*>(str) - explicit about removing const

    std::cout << "C++ casts are:\n";
    std::cout << "  1. More explicit about intent\n";
    std::cout << "  2. Easier to search for in code\n";
    std::cout << "  3. Sometimes catch errors at compile time\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_type_casting() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 13: Static and Dynamic Type Casting\n";
    std::cout << "========================================\n";

    example_static_cast();
    challenge_static_cast();

    example_dynamic_cast();
    challenge_dynamic_cast();

    example_reinterpret_cast();
    challenge_reinterpret_cast();

    example_const_cast();
    challenge_const_cast();

    example_cstyle_vs_cpp_casts();

    std::cout << "\n========================================\n";
    std::cout << "Type Casting exercise complete!\n";
    std::cout << "========================================\n";
}
