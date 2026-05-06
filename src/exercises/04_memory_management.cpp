#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cstring>
#include <array>
#include <numeric>

// ============================================================
// EXERCISE 4: Memory Management
// ============================================================

// CONCEPT: Memory Pools
// - Pre-allocate a block of memory and manage allocations manually
// - Reduces fragmentation and allocation overhead
// - Useful for fixed-size objects in game engines, real-time systems

class MemoryPool {
public:
    MemoryPool(size_t blockSize, size_t blockCount)
        : blockSize_(blockSize), blockCount_(blockCount) {
        memory_ = new char[blockSize * blockCount];
        for (size_t i = 0; i < blockCount; ++i) {
            freeBlocks_.push_back(memory_ + (i * blockSize));
        }
        std::cout << "MemoryPool created: " << blockCount
                  << " blocks of " << blockSize << " bytes\n";
    }

    ~MemoryPool() {
        delete[] memory_;
        std::cout << "MemoryPool destroyed\n";
    }

    void* allocate() {
        if (freeBlocks_.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeBlocks_.back();
        freeBlocks_.pop_back();
        return block;
    }

    void deallocate(void* ptr) {
        freeBlocks_.push_back(static_cast<char*>(ptr));
    }

    size_t availableBlocks() const { return freeBlocks_.size(); }

private:
    size_t blockSize_;
    size_t blockCount_;
    char* memory_;
    std::vector<char*> freeBlocks_;
};

void example_memory_pool() {
    std::cout << "\n=== Memory Pool Example ===\n";

    MemoryPool pool(sizeof(int), 5);

    std::cout << "Available blocks: " << pool.availableBlocks() << "\n";

    int* p1 = static_cast<int*>(pool.allocate());
    *p1 = 42;
    std::cout << "Allocated p1 = " << *p1 << "\n";
    std::cout << "Available blocks: " << pool.availableBlocks() << "\n";

    int* p2 = static_cast<int*>(pool.allocate());
    *p2 = 100;
    std::cout << "Allocated p2 = " << *p2 << "\n";
    std::cout << "Available blocks: " << pool.availableBlocks() << "\n";

    pool.deallocate(p1);
    std::cout << "Deallocated p1, available: " << pool.availableBlocks() << "\n";

    int* p3 = static_cast<int*>(pool.allocate());
    *p3 = 200;
    std::cout << "Allocated p3 = " << *p3 << "\n";
    std::cout << "Available blocks: " << pool.availableBlocks() << "\n";
}

// CHALLENGE 4.1: Create a memory pool for objects of size 64 bytes with 10 blocks.
// Allocate 3 blocks, store different values in each, then deallocate the middle one.
void challenge_memory_pool() {
    std::cout << "\n--- Challenge 4.1: Memory pool operations ---\n";

    // TODO: Create a MemoryPool with blockSize=64, blockCount=10

    // TODO: Allocate 3 blocks and store a different integer in each

    // TODO: Print the values stored in each block

    // TODO: Deallocate the second block (middle one)

    // TODO: Print available blocks count (should be 8)

    // TODO: Allocate one more block and verify it reuses the deallocated memory

    std::cout << "Challenge 4.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Stack Allocator
// - Allocation from a fixed-size stack buffer
// - Extremely fast: just increment a pointer
// - No fragmentation, but LIFO deallocation required
// - Used in embedded systems, game loops, temporary allocations

class StackAllocator {
public:
    explicit StackAllocator(size_t size) : size_(size) {
        memory_ = new char[size];
        offset_ = 0;
        std::cout << "StackAllocator created: " << size << " bytes\n";
    }

    ~StackAllocator() {
        delete[] memory_;
        std::cout << "StackAllocator destroyed\n";
    }

    void* allocate(size_t bytes) {
        if (offset_ + bytes > size_) {
            throw std::bad_alloc();
        }
        void* ptr = memory_ + offset_;
        offset_ += bytes;
        return ptr;
    }

    void reset() {
        offset_ = 0;
        std::cout << "StackAllocator reset\n";
    }

    size_t used() const { return offset_; }
    size_t remaining() const { return size_ - offset_; }

private:
    size_t size_;
    size_t offset_;
    char* memory_;
};

void example_stack_allocator() {
    std::cout << "\n=== Stack Allocator Example ===\n";

    StackAllocator allocator(1024);
    std::cout << "Initial: used=" << allocator.used()
              << ", remaining=" << allocator.remaining() << "\n";

    int* numbers = static_cast<int*>(allocator.allocate(10 * sizeof(int)));
    for (int i = 0; i < 10; ++i) {
        numbers[i] = i * 10;
    }
    std::cout << "Allocated 10 ints, used=" << allocator.used() << "\n";
    std::cout << "numbers[5] = " << numbers[5] << "\n";

    struct Entity {
        float x, y, z;
        int id;
    };

    Entity* entity = static_cast<Entity*>(allocator.allocate(sizeof(Entity)));
    entity->x = 1.0f;
    entity->y = 2.0f;
    entity->z = 3.0f;
    entity->id = 42;

    std::cout << "Entity: (" << entity->x << ", " << entity->y << ", "
              << entity->z << ") id=" << entity->id << "\n";
    std::cout << "Used: " << allocator.used() << " bytes\n";

    allocator.reset();
    std::cout << "After reset: used=" << allocator.used() << "\n";
}

// CHALLENGE 4.2: Use a stack allocator to allocate space for a string
// (including null terminator), copy "Hello Stack!" into it, and print it.
// Then allocate an array of 5 doubles and fill with values 0.5, 1.0, 1.5, 2.0, 2.5
void challenge_stack_allocator() {
    std::cout << "\n--- Challenge 4.2: Stack allocator with string and array ---\n";

    StackAllocator allocator(256);

    // TODO: Allocate space for "Hello Stack!" (13 bytes including null terminator)

    // TODO: Copy the string into the allocated memory (use std::strcpy or memcpy)

    // TODO: Print the string

    // TODO: Allocate space for 5 doubles

    // TODO: Fill with values 0.5, 1.0, 1.5, 2.0, 2.5 and print them

    // TODO: Print total bytes used

    std::cout << "Challenge 4.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: RAII Wrappers for C Resources
// - Wrap C-style resources (FILE*, malloc, sockets) in C++ classes
// - Automatic cleanup via destructors
// - Exception-safe resource management

class ScopedFile {
public:
    ScopedFile(const char* filename, const char* mode)
        : file_(std::fopen(filename, mode)) {
        if (!file_) {
            throw std::runtime_error("Failed to open file: " + std::string(filename));
        }
        std::cout << "Opened file: " << filename << "\n";
    }

    ~ScopedFile() {
        if (file_) {
            std::fclose(file_);
            std::cout << "File closed automatically\n";
        }
    }

    FILE* get() const { return file_; }

    // Prevent copying
    ScopedFile(const ScopedFile&) = delete;
    ScopedFile& operator=(const ScopedFile&) = delete;

    // Allow moving
    ScopedFile(ScopedFile&& other) noexcept : file_(other.file_) {
        other.file_ = nullptr;
    }

private:
    FILE* file_;
};

void example_raii_file() {
    std::cout << "\n=== RAII File Wrapper Example ===\n";

    const char* testFile = "/tmp/raii_test.txt";

    {
        ScopedFile writer(testFile, "w");
        const char* msg = "Hello from RAII!\n";
        std::fwrite(msg, 1, std::strlen(msg), writer.get());
        std::cout << "Wrote to file inside scope\n";
    }

    {
        ScopedFile reader(testFile, "r");
        char buffer[256] = {};
        size_t bytes = std::fread(buffer, 1, sizeof(buffer) - 1, reader.get());
        std::cout << "Read " << bytes << " bytes: " << buffer << "\n";
    }

    std::remove(testFile);
}

// CHALLENGE 4.3: Create a ScopedMemory class that wraps malloc/free
// The constructor takes a size and calls malloc, the destructor calls free
// Provide a get() method to access the raw pointer
void challenge_raii_memory() {
    std::cout << "\n--- Challenge 4.3: ScopedMemory RAII wrapper ---\n";

    // TODO: Define a ScopedMemory class with:
    //   - Constructor that takes size_t and calls malloc
    //   - Destructor that calls free
    //   - get() method returning void*
    //   - Deleted copy constructor/assignment
    //   - Move constructor/assignment

    // TODO: Use ScopedMemory to allocate 100 bytes
    // TODO: Fill with values 0-99
    // TODO: Print first 5 and last 5 values
    // TODO: Verify automatic cleanup when scope ends

    std::cout << "Challenge 4.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Buffer/View Pattern
// - Non-owning reference to a memory region
// - Avoids copying while providing bounds checking
// - Similar to std::string_view but for arbitrary data

class BufferView {
public:
    BufferView(const void* data, size_t size)
        : data_(static_cast<const char*>(data)), size_(size) {}

    const char* data() const { return data_; }
    size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    char operator[](size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("BufferView index out of range");
        }
        return data_[index];
    }

    BufferView slice(size_t offset, size_t length) const {
        if (offset + length > size_) {
            throw std::out_of_range("BufferView slice out of range");
        }
        return BufferView(data_ + offset, length);
    }

private:
    const char* data_;
    size_t size_;
};

void example_buffer_view() {
    std::cout << "\n=== BufferView Example ===\n";

    std::vector<int> data = {10, 20, 30, 40, 50};
    BufferView view(data.data(), data.size() * sizeof(int));

    std::cout << "View size: " << view.size() << " bytes\n";

    // Slice the view to skip first element
    BufferView sliced = view.slice(sizeof(int), (data.size() - 1) * sizeof(int));
    const int* slicedData = reinterpret_cast<const int*>(sliced.data());
    std::cout << "Sliced view (skip first): ";
    for (size_t i = 0; i < sliced.size() / sizeof(int); ++i) {
        std::cout << slicedData[i] << " ";
    }
    std::cout << "\n";

    // Bounds checking
    try {
        char val = view[view.size() + 100];
        (void)val;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
}

// CHALLENGE 4.4: Create a buffer containing ASCII values 'A' through 'Z',
// create a BufferView of it, then slice out the middle 10 characters
// and print them as characters.
void challenge_buffer_view() {
    std::cout << "\n--- Challenge 4.4: BufferView with alphabet ---\n";

    // TODO: Create a vector<char> with values 'A' through 'Z' (26 letters)

    // TODO: Create a BufferView of the entire vector

    // TODO: Print the full view size

    // TODO: Slice out the middle 10 characters (start at index 8, length 10)

    // TODO: Print the sliced characters (should be 'I' through 'R')

    std::cout << "Challenge 4.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_memory_management() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 4: Memory Management\n";
    std::cout << "========================================\n";

    example_memory_pool();
    challenge_memory_pool();

    example_stack_allocator();
    challenge_stack_allocator();

    example_raii_file();
    challenge_raii_memory();

    example_buffer_view();
    challenge_buffer_view();

    std::cout << "\n========================================\n";
    std::cout << "Memory Management exercise complete!\n";
    std::cout << "========================================\n";
}
