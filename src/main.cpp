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
#include "exercises/16_threads_sync.h"
#include "exercises/17_processes.h"
#include "exercises/18_ipc.h"
#include "exercises/19_skip_lists.h"
#include "exercises/20_window_basics.h"
#include "exercises/21_colors_blending.h"
#include "exercises/22_lines_curves.h"
#include "exercises/23_polygons_triangles.h"
#include "exercises/24_text_fonts.h"
#include "exercises/25_keyboard_input.h"
#include "exercises/26_mouse_input.h"
#include "exercises/27_gamepad_input.h"
#include "exercises/28_2d_transformations.h"
#include "exercises/29_textures_sprites.h"
#include "exercises/30_sprite_sheets.h"
#include "exercises/31_image_manipulation.h"
#include "exercises/32_render_textures.h"
#include "exercises/33_sound_effects.h"
#include "exercises/34_music_streaming.h"
#include "exercises/35_camera_2d.h"
#include "exercises/36_camera_3d.h"
#include "exercises/37_3d_shapes.h"
#include "exercises/38_3d_models.h"
#include "exercises/39_materials_textures.h"
#include "exercises/40_lighting.h"
#include "exercises/41_shaders_basics.h"
#include "exercises/42_collision_detection.h"
#include "exercises/43_raycasting.h"
#include "exercises/44_particle_systems.h"
#include "exercises/45_ui_elements.h"
#include "exercises/46_tilemaps.h"
#include "exercises/47_state_machines.h"
#include "exercises/48_physics_basics.h"
#include "exercises/49_mini_game.h"
#include "exercises/50_entt_basics.h"
#include "exercises/51_entt_components.h"
#include "exercises/52_entt_views_groups.h"
#include "exercises/53_entt_events.h"
#include "exercises/54_entt_raylib.h"
#include "exercises/55_2d_animations.h"
#include "exercises/56_multi_window.h"
#include "exercises/57_3d_terrain.h"
#include "exercises/58_split_screen.h"
#include "exercises/59_gesture_detection.h"
#include "exercises/60_dropdown_combobox.h"
#include "exercises/61_scene_graph.h"
#include "exercises/62_save_load.h"
#include "exercises/63_multithreaded_loading.h"
#include "exercises/64_final_project.h"

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
        {"16", []() { exercise_threads_sync(); }},
        {"17", []() { exercise_processes(); }},
        {"18", []() { exercise_ipc(); }},
        {"19", []() { exercise_skip_lists(); }},
        {"20", []() { exercise_window_basics(); }},
        {"21", []() { exercise_colors_blending(); }},
        {"22", []() { exercise_lines_curves(); }},
        {"23", []() { exercise_polygons_triangles(); }},
        {"24", []() { exercise_text_fonts(); }},
        {"25", []() { exercise_keyboard_input(); }},
        {"26", []() { exercise_mouse_input(); }},
        {"27", []() { exercise_gamepad_input(); }},
        {"28", []() { exercise_2d_transformations(); }},
        {"29", []() { exercise_textures_sprites(); }},
        {"30", []() { exercise_sprite_sheets(); }},
        {"31", []() { exercise_image_manipulation(); }},
        {"32", []() { exercise_render_textures(); }},
        {"33", []() { exercise_sound_effects(); }},
        {"34", []() { exercise_music_streaming(); }},
        {"35", []() { exercise_camera_2d(); }},
        {"36", []() { exercise_camera_3d(); }},
        {"37", []() { exercise_3d_shapes(); }},
        {"38", []() { exercise_3d_models(); }},
        {"39", []() { exercise_materials_textures(); }},
        {"40", []() { exercise_lighting(); }},
        {"41", []() { exercise_shaders_basics(); }},
        {"42", []() { exercise_collision_detection(); }},
        {"43", []() { exercise_raycasting(); }},
        {"44", []() { exercise_particle_systems(); }},
        {"45", []() { exercise_ui_elements(); }},
        {"46", []() { exercise_tilemaps(); }},
        {"47", []() { exercise_state_machines(); }},
        {"48", []() { exercise_physics_basics(); }},
        {"49", []() { exercise_mini_game(); }},
        {"50", []() { exercise_entt_basics(); }},
        {"51", []() { exercise_entt_components(); }},
        {"52", []() { exercise_entt_views_groups(); }},
        {"53", []() { exercise_entt_events(); }},
        {"54", []() { exercise_entt_raylib(); }},
        {"55", []() { exercise_2d_animations(); }},
        {"56", []() { exercise_multi_window(); }},
        {"57", []() { exercise_3d_terrain(); }},
        {"58", []() { exercise_split_screen(); }},
        {"59", []() { exercise_gesture_detection(); }},
        {"60", []() { exercise_dropdown_combobox(); }},
        {"61", []() { exercise_scene_graph(); }},
        {"62", []() { exercise_save_load(); }},
        {"63", []() { exercise_multithreaded_loading(); }},
        {"64", []() { exercise_final_project(); }},
    };

    std::cout << "C++ Training Exercises\n";
    std::cout << "======================\n";
    std::cout << " 1. Smart Pointers (unique_ptr, shared_ptr, weak_ptr)\n";
    std::cout << " 2. STL Algorithms (find, transform, accumulate, sort)\n";
    std::cout << " 3. C++17 Additions (optional, variant, any, string_view)\n";
    std::cout << " 4. Memory Management (pools, stack allocators, RAII)\n";
    std::cout << " 5. String Processing (regex, formatting, conversion)\n";
    std::cout << " 6. Boost.Asio Networking (TCP, UDP, async I/O)\n";
    std::cout << " 7. Boost Memory (pool, object_pool, singleton_pool)\n";
    std::cout << " 8. Boost Graph (BFS, DFS, Dijkstra, topological sort)\n";
    std::cout << " 9. Boost Container (flat_map, stable_vector, static_vector)\n";
    std::cout << "10. Pointers and References (raw pointers, references, move semantics)\n";
    std::cout << "11. Matrix Operations and Terminal Formatting (matrix math, ANSI colors)\n";
    std::cout << "12. Signals, IRQ, and DMA (POSIX signals, interrupts, DMA)\n";
    std::cout << "13. Static and Dynamic Type Casting (static_cast, dynamic_cast, reinterpret_cast, const_cast)\n";
    std::cout << "14. ECS with STL (Entity Component System using unordered_map, vector)\n";
    std::cout << "15. Lambda Functions (capture, mutable, generic, higher-order)\n";
    std::cout << "16. Threads and Synchronization (thread, mutex, condition_variable, async, atomic)\n";
    std::cout << "17. Processes and System Calls (fork, exec, wait, system)\n";
    std::cout << "18. Inter-Process Communication (pipes, FIFO, shared memory, Boost.Interprocess, signals)\n";
    std::cout << "19. Skip Lists (probabilistic data structure, Redis sorted sets, range queries)\n";
    std::cout << "--- Raylib Exercises ---\n";
    std::cout << "20. Window & Basics (InitWindow, shapes, FPS)\n";
    std::cout << "21. Colors & Blending (Color struct, alpha, Fade)\n";
    std::cout << "22. Lines & Curves (DrawLine, beziers, splines)\n";
    std::cout << "23. Polygons & Triangles (DrawPoly, DrawTriangle)\n";
    std::cout << "24. Text & Fonts (DrawText, LoadFont, formatting)\n";
    std::cout << "25. Keyboard Input (WASD, key events, typing)\n";
    std::cout << "26. Mouse Input (click, drag, wheel, drawing)\n";
    std::cout << "27. Gamepad Input (controller detection, joystick)\n";
    std::cout << "28. 2D Transformations (rotation, scale, origin)\n";
    std::cout << "29. Textures & Sprites (LoadTexture, DrawTexture)\n";
    std::cout << "30. Sprite Sheets (DrawTexturePro, frame animation)\n";
    std::cout << "31. Image Manipulation (resize, flip, tint, paint)\n";
    std::cout << "32. Render Textures (off-screen rendering, effects)\n";
    std::cout << "33. Sound Effects (tone generation, playback)\n";
    std::cout << "34. Music Streaming (play, pause, seek, visualize)\n";
    std::cout << "35. Camera 2D (follow, zoom, rotation, shake)\n";
    std::cout << "36. Camera 3D (orbital, first-person, projection)\n";
    std::cout << "37. 3D Shapes (cube, sphere, cylinder, torus)\n";
    std::cout << "38. 3D Models (procedural meshes, animation)\n";
    std::cout << "39. Materials & Textures (albedo maps, tinting)\n";
    std::cout << "40. Lighting (simulated light sources, colored lights)\n";
    std::cout << "41. Shaders Basics (post-processing, GLSL effects)\n";
    std::cout << "42. Collision Detection (rect, circle, point)\n";
    std::cout << "43. Raycasting (mouse picking, 3D selection)\n";
    std::cout << "44. Particle Systems (emitter, rain, fireworks)\n";
    std::cout << "45. UI Elements (buttons, sliders, checkboxes)\n";
    std::cout << "46. Tilemaps (grid, camera scrolling, procedural)\n";
    std::cout << "47. State Machines (MENU, PLAYING, PAUSED, GAMEOVER)\n";
    std::cout << "48. Physics Basics (gravity, bounce, projectile)\n";
    std::cout << "49. Mini Game (complete space shooter)\n";
    std::cout << "--- EnTT Exercises ---\n";
    std::cout << "50. EnTT Entities (create, destroy, valid)\n";
    std::cout << "51. EnTT Components (assign, get, remove, patch)\n";
    std::cout << "52. EnTT Views & Groups (iteration, filters, sort)\n";
    std::cout << "53. EnTT Events & Dispatchers (sink, trigger, enqueue)\n";
    std::cout << "54. EnTT + raylib Integration (ECS Space Shooter)\n";
    std::cout << "--- raylib Advanced ---\n";
    std::cout << "55. 2D Animations & Tweening (easing, lerp, bounce)\n";
    std::cout << "56. Multi-Window & Monitor Handling (flags, fullscreen)\n";
    std::cout << "57. 3D Terrain (heightmap, noise, procedural generation)\n";
    std::cout << "58. Split-Screen & Multi-Viewport Rendering\n";
    std::cout << "59. Gesture Detection (touch, swipe, pinch, drag)\n";
    std::cout << "60. Dropdown & Combo Box UI (custom widgets)\n";
    std::cout << "61. Scene Graph / Node Hierarchy (robot arm)\n";
    std::cout << "62. Save & Load System (serialization, file I/O)\n";
    std::cout << "63. Multi-Threaded Loading (async, progress bar)\n";
    std::cout << "64. Final Project — ECS Tower Defense\n";
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
        std::cout << "\nSelect exercise (0-64, q to quit): ";
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
