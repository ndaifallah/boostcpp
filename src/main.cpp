#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include "exercises/01_smart_pointers.h"
#include "exercises/02_stl_algorithms.h"
#include "exercises/03_cpp17_additions.h"

int main(int argc, char* argv[]) {
    std::unordered_map<std::string, std::function<void()>> exercises = {
        {"1", []() { exercise_smart_pointers(); }},
        {"2", []() { exercise_stl_algorithms(); }},
        {"3", []() { exercise_cpp17_additions(); }},
    };

    std::cout << "C++ Training Exercises\n";
    std::cout << "======================\n";
    std::cout << "1. Smart Pointers (unique_ptr, shared_ptr, weak_ptr)\n";
    std::cout << "2. STL Algorithms (find, transform, accumulate, sort)\n";
    std::cout << "3. C++17 Additions (optional, variant, any, string_view)\n";
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
        std::cout << "\nSelect exercise (0-3, q to quit): ";
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
