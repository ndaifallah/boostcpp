#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <chrono>

// ============================================================
// EXERCISE 16: Threads and Synchronization
// ============================================================

// CONCEPT: Basic std::thread
// - Create threads with callable objects (functions, lambdas, functors)
// - join() blocks until thread finishes
// - detach() lets thread run independently (daemon thread)
// - Always join or detach before thread object destructor runs

void example_thread_basic() {
    std::cout << "\n=== Basic Thread Creation ===\n";

    // Thread from free function
    auto worker = [](int id) {
        std::cout << "  Worker " << id << " running on thread "
                  << std::this_thread::get_id() << "\n";
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);

    std::cout << "  Main thread: " << std::this_thread::get_id() << "\n";

    t1.join();
    t2.join();
    std::cout << "  Both workers joined\n";
}

// CHALLENGE 16.1: Create 3 threads, each printing the numbers 1..5.
// Ensure main waits for all threads to finish.
void challenge_thread_basic() {
    std::cout << "\n--- Challenge 16.1: Launch and join threads ---\n";

    // TODO: Define a lambda that prints numbers 1..5 with its thread id

    // TODO: Create 3 std::thread objects running the lambda

    // TODO: join all 3 threads

    std::cout << "Challenge 16.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::mutex and std::lock_guard
// - mutex protects shared data from concurrent access
// - lock_guard acquires mutex on construction, releases on destruction (RAII)
// - Always prefer lock_guard over manual lock/unlock

std::mutex mtx_print;

void safe_print(const std::string& msg) {
    std::lock_guard<std::mutex> lock(mtx_print);
    std::cout << msg << "\n";
}

void example_mutex() {
    std::cout << "\n=== Mutex and Lock Guard ===\n";

    auto work = [](int id) {
        for (int i = 0; i < 3; ++i) {
            safe_print("  Thread " + std::to_string(id) + " iteration " +
                       std::to_string(i));
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };

    std::thread t1(work, 1);
    std::thread t2(work, 2);
    t1.join();
    t2.join();
}

// CHALLENGE 16.2: Use a mutex-protected shared counter incremented
// by 10 threads (1000 increments each). Verify the final count.
void challenge_mutex_counter() {
    std::cout << "\n--- Challenge 16.2: Shared counter with mutex ---\n";

    // TODO: Create a shared int counter = 0 and a std::mutex mtx

    // TODO: Lambda: for 0..999 increment counter under lock

    // TODO: Launch 10 threads running the lambda

    // TODO: Join all threads, print counter (expected: 10000)

    std::cout << "Challenge 16.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::condition_variable
// - Blocks threads until notified by another thread
// - Used with std::unique_lock and a predicate (to avoid spurious wakeups)
// - notify_one() wakes one waiter, notify_all() wakes all

void example_condition_variable() {
    std::cout << "\n=== Condition Variable ===\n";

    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    auto waiter = [&]() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&ready]() { return ready; });
        std::cout << "  Waiter thread proceeding after notification\n";
    };

    auto notifier = [&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        {
            std::lock_guard<std::mutex> lock(mtx);
            ready = true;
        }
        cv.notify_one();
        std::cout << "  Notifier thread sent notification\n";
    };

    std::thread t1(waiter);
    std::thread t2(notifier);
    t1.join();
    t2.join();
}

// CHALLENGE 16.3: Implement a simple producer-consumer using
// condition_variable. Producer pushes 5 items, consumer pops them.
void challenge_producer_consumer() {
    std::cout << "\n--- Challenge 16.3: Producer-Consumer ---\n";

    // TODO: Shared queue<int>, mutex, cv, bool done

    // TODO: Producer lambda pushes numbers 1..5, notifies consumer

    // TODO: Consumer lambda waits and prints each item

    // TODO: Launch producer and consumer threads, join them

    std::cout << "Challenge 16.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::async and std::future
// - std::async launches a task (potentially in a separate thread)
// - Returns std::future which holds the result
// - future.get() blocks until result is ready
// - Launch policy: std::launch::async (new thread) or deferred (lazy)

int compute_square(int x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    return x * x;
}

void example_async() {
    std::cout << "\n=== Async and Future ===\n";

    std::future<int> result = std::async(std::launch::async, compute_square, 7);
    std::cout << "  Waiting for async result...\n";
    int value = result.get();
    std::cout << "  Async result: " << value << "\n";

    // Multiple async tasks
    std::vector<std::future<int>> futures;
    for (int i = 1; i <= 5; ++i) {
        futures.push_back(std::async(std::launch::async, compute_square, i));
    }

    int sum = 0;
    for (auto& f : futures) {
        sum += f.get();
    }
    std::cout << "  Sum of squares 1..5 = " << sum << "\n";
}

// CHALLENGE 16.4: Use std::async to compute factorials of 5, 7, and 10
// in parallel. Print each result.
void challenge_async_factorial() {
    std::cout << "\n--- Challenge 16.4: Parallel factorial with async ---\n";

    // TODO: Write a function that computes factorial

    // TODO: Launch async tasks for 5, 7, 10

    // TODO: Collect results via future.get() and print them

    std::cout << "Challenge 16.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: std::atomic
// - Lock-free atomic operations on shared data
// - No mutex needed for simple types (int, bool, pointer)
// - Supports: load, store, exchange, fetch_add, etc.
// - Memory ordering parameters for fine-grained control

void example_atomic() {
    std::cout << "\n=== Atomic Operations ===\n";

    std::atomic<int> counter{0};

    auto worker = [&counter](int iterations) {
        for (int i = 0; i < iterations; ++i) {
            counter.fetch_add(1);
        }
    };

    std::thread t1(worker, 100000);
    std::thread t2(worker, 100000);
    t1.join();
    t2.join();

    std::cout << "  Atomic counter: " << counter.load() << " (expected: 200000)\n";
}

// CHALLENGE 16.5: Use std::atomic<bool> as a flag to stop a worker thread
// cleanly after main waits 100ms.
void challenge_atomic_flag() {
    std::cout << "\n--- Challenge 16.5: Atomic flag for thread stopping ---\n";

    // TODO: std::atomic<bool> stop{false};

    // TODO: Worker lambda loops printing "." every 10ms until stop is true

    // TODO: Main sleeps 100ms, sets stop = true, joins worker

    std::cout << "Challenge 16.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges

void exercise_threads_sync() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 16: Threads and Synchronization\n";
    std::cout << "========================================\n";

    example_thread_basic();
    challenge_thread_basic();

    example_mutex();
    challenge_mutex_counter();

    example_condition_variable();
    challenge_producer_consumer();

    example_async();
    challenge_async_factorial();

    example_atomic();
    challenge_atomic_flag();

    std::cout << "\n========================================\n";
    std::cout << "Threads and Synchronization complete!\n";
    std::cout << "========================================\n";
}
