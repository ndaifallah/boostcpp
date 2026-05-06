#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "exercises/01_smart_pointers.h"
#include "exercises/02_stl_algorithms.h"
#include "exercises/03_cpp17_additions.h"
#include "exercises/04_memory_management.h"
#include "exercises/05_string_processing.h"
#include "exercises/06_asio_networking.h"
#include "exercises/07_boost_memory.h"
#include "exercises/08_boost_graph.h"
#include "exercises/09_boost_container.h"
#include "exercises/10_pointers_references.h"
#include "exercises/11_matrix_formatting.h"
#include "exercises/12_systems_hardware.h"
#include "exercises/13_type_casting.h"
#include "exercises/14_ecs_stl.h"
#include "exercises/15_lambda_functions.h"

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, std::function<void()>> exercises = {
        {"1", []() { exercise_smart_pointers(); }},
        {"2", []() { exercise_stl_algorithms(); }},
        {"3", []() { exercise_cpp17_additions(); }},
        {"4", []() { exercise_memory_management(); }},
        {"5", []() { exercise_string_processing(); }},
        {"6", []() { exercise_asio_networking(); }},
        {"7", []() { exercise_boost_memory(); }},
        {"8", []() { exercise_boost_graph(); }},
        {"9", []() { exercise_boost_container(); }},
        {"10", []() { exercise_pointers_references(); }},
        {"11", []() { exercise_matrix_formatting(); }},
        {"12", []() { exercise_systems_hardware(); }},
        {"13", []() { exercise_type_casting(); }},
        {"14", []() { exercise_ecs_stl(); }},
        {"15", []() { exercise_lambda_functions(); }},
    };

    std::cout << "C++ Training Exercises\n";
    std::cout << "======================\n";
    std::cout << "1. Smart Pointers (unique_ptr, shared_ptr, weak_ptr)\n";
    std::cout << "2. STL Algorithms (find, transform, accumulate, sort)\n";
    std::cout << "3. C++17 Additions (optional, variant, any, string_view)\n";
    std::cout << "4. Memory Management (pools, stack allocators, RAII)\n";
    std::cout << "5. String Processing (regex, formatting, conversion)\n";
    std::cout << "6. Boost.Asio Networking (TCP, UDP, async I/O)\n";
    std::cout << "7. Boost Memory (pool, object_pool, singleton_pool)\n";
    std::cout << "8. Boost Graph (BFS, DFS, Dijkstra, topological sort)\n";
    std::cout << "9. Boost Container (flat_map, stable_vector, static_vector)\n";
    std::cout << "10. Pointers and References (raw pointers, references, move semantics)\n";
    std::cout << "11. Matrix Operations and Terminal Formatting (matrix math, ANSI colors)\n";
    std::cout << "12. Signals, IRQ, and DMA (POSIX signals, interrupts, DMA)\n";
    std::cout << "13. Static and Dynamic Type Casting (static_cast, dynamic_cast, reinterpret_cast, const_cast)\n";
    std::cout << "14. ECS with STL (Entity Component System using unordered_map, vector)\n";
    std::cout << "15. Lambda Functions (capture, mutable, generic, higher-order)\n";
    std::cout << "0. Run all exercises\n";
    std::cout << "q. Quit\n";
    std::cout << "======================\n";

    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "0") {
            for (const auto& [key, fn] : exercises) fn();
            return 0;
        }
        if (exercises.count(arg)) {
            exercises[arg]();
            return 0;
        }
        std::cout << "Unknown exercise: " << arg << "\n";
        return 1;
    }

    while (true) {
        std::cout << "\nSelect exercise (0-15, q to quit): ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "q" || input == "Q") {
            std::cout << "Goodbye!\n";
            break;
        }

        if (input == "0") {
            for (const auto& [key, fn] : exercises) fn();
        } else if (exercises.count(input)) {
            exercises[input]();
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
