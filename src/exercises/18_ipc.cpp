#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <csignal>
#include <cstdlib>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace bip = boost::interprocess;

// ============================================================
// EXERCISE 18: Inter-Process Communication (IPC)
// ============================================================

// CONCEPT: Pipes (pipe())
// - pipe(int fd[2]) creates a unidirectional data channel
// - fd[0] is read end, fd[1] is write end
// - Used between related processes (parent-child)
// - write() to fd[1], read() from fd[0]

void example_pipe() {
    std::cout << "\n=== Basic Pipe ===\n";

    int fd[2];
    if (pipe(fd) == -1) {
        std::cerr << "  pipe() failed\n";
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child: write to pipe
        close(fd[0]);  // close unused read end
        const char* msg = "Hello from child!";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
        _exit(0);
    } else if (pid > 0) {
        // Parent: read from pipe
        close(fd[1]);  // close unused write end
        char buffer[128] = {0};
        read(fd[0], buffer, sizeof(buffer));
        std::cout << "  Parent received: " << buffer << "\n";
        close(fd[0]);
        waitpid(pid, nullptr, 0);
    }
}

// CHALLENGE 18.1: Create a pipe between parent and child.
// Child sends the numbers 1..5 as a comma-separated string.
// Parent reads and prints "Received: 1,2,3,4,5".
void challenge_pipe() {
    std::cout << "\n--- Challenge 18.1: Pipe numbers ---\n";

    // TODO: pipe(), fork()

    // TODO: Child: build "1,2,3,4,5" string, write to pipe

    // TODO: Parent: read from pipe, print "Received: <data>"

    // TODO: close appropriate ends, waitpid

    std::cout << "Challenge 18.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Named Pipes (FIFO)
// - mkfifo() creates a named pipe visible in the filesystem
// - Unrelated processes can communicate via FIFO
// - Use open/read/write just like a regular file

void example_fifo() {
    std::cout << "\n=== Named Pipe (FIFO) ===\n";
    const char* fifo_path = "/tmp/boost_example_fifo";

    // Create FIFO
    mkfifo(fifo_path, 0666);

    pid_t pid = fork();

    if (pid == 0) {
        // Child: writer
        int fd = open(fifo_path, O_WRONLY);
        const char* msg = "FIFO message";
        write(fd, msg, strlen(msg) + 1);
        close(fd);
        _exit(0);
    } else if (pid > 0) {
        // Parent: reader
        int fd = open(fifo_path, O_RDONLY);
        char buffer[128] = {0};
        read(fd, buffer, sizeof(buffer));
        std::cout << "  FIFO received: " << buffer << "\n";
        close(fd);
        waitpid(pid, nullptr, 0);
        unlink(fifo_path);  // clean up
    }
}

// CHALLENGE 18.2: Create a FIFO at /tmp/boost_challenge_fifo.
// Fork, child writes "Challenge data", parent reads and prints it.
void challenge_fifo() {
    std::cout << "\n--- Challenge 18.2: FIFO challenge ---\n";

    // TODO: mkfifo("/tmp/boost_challenge_fifo", 0666)

    // TODO: fork(), child writes "Challenge data", parent reads

    // TODO: unlink the fifo at the end

    std::cout << "Challenge 18.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: POSIX Shared Memory (shm_open + mmap)
// - shm_open() creates/opens a shared memory object
// - ftruncate() sets the size
// - mmap() maps it into process address space
// - Both processes can read/write the same memory

void example_posix_shm() {
    std::cout << "\n=== POSIX Shared Memory ===\n";
    const char* shm_name = "/boost_example_shm";
    const size_t size = 256;

    // Create shared memory
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, size);

    pid_t pid = fork();

    if (pid == 0) {
        // Child: write to shared memory
        void* ptr = mmap(nullptr, size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        std::strcpy(static_cast<char*>(ptr), "Shared memory from child!");
        munmap(ptr, size);
        close(shm_fd);
        _exit(0);
    } else if (pid > 0) {
        waitpid(pid, nullptr, 0);
        // Parent: read from shared memory
        void* ptr = mmap(nullptr, size, PROT_READ, MAP_SHARED, shm_fd, 0);
        std::cout << "  Parent read: " << static_cast<char*>(ptr) << "\n";
        munmap(ptr, size);
        close(shm_fd);
        shm_unlink(shm_name);  // clean up
    }
}

// CHALLENGE 18.3: Use POSIX shared memory to pass an integer counter
// from child to parent. Child writes 42, parent reads and prints it.
void challenge_posix_shm() {
    std::cout << "\n--- Challenge 18.3: POSIX shared memory counter ---\n";

    // TODO: shm_open, ftruncate

    // TODO: fork, child mmap + write int(42)

    // TODO: parent wait, mmap + read + print int

    // TODO: munmap, close, shm_unlink

    std::cout << "Challenge 18.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Boost.Interprocess Shared Memory
// - Cross-platform shared memory via Boost
// - bip::shared_memory_object: create/open shared memory
// - bip::mapped_region: map into process address space

void example_boost_shm() {
    std::cout << "\n=== Boost.Interprocess Shared Memory ===\n";
    const char* name = "boost_ipc_example";

    // Remove previous instance
    bip::shared_memory_object::remove(name);

    pid_t pid = fork();

    if (pid == 0) {
        // Child: create and write
        bip::shared_memory_object shm(
            bip::open_or_create, name, bip::read_write);
        shm.truncate(256);
        bip::mapped_region region(shm, bip::read_write);
        std::memset(region.get_address(), 0, region.get_size());
        std::strcpy(static_cast<char*>(region.get_address()),
                    "Boost IPC message");
        _exit(0);
    } else if (pid > 0) {
        waitpid(pid, nullptr, 0);
        // Parent: open and read
        bip::shared_memory_object shm(
            bip::open_only, name, bip::read_only);
        bip::mapped_region region(shm, bip::read_only);
        const char* msg = static_cast<const char*>(region.get_address());
        std::cout << "  Boost shared memory: " << msg << "\n";
        bip::shared_memory_object::remove(name);
    }
}

// CHALLENGE 18.4: Use Boost.Interprocess to share an array of 5 integers
// between parent and child. Child writes {10,20,30,40,50}, parent reads.
void challenge_boost_shm() {
    std::cout << "\n--- Challenge 18.4: Boost shared memory array ---\n";

    // TODO: bip::shared_memory_object::remove("boost_challenge")

    // TODO: fork
    // Child: create/open shm, truncate, mmap region, write int[5]
    // Parent: wait, open read-only, read and print int[5]

    // TODO: cleanup

    std::cout << "Challenge 18.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Signals (software interrupts for IPC)
// - kill(pid, sig) sends a signal to a process
// - Signal handlers installed via std::signal() or sigaction()
// - SIGUSR1 and SIGUSR2 are reserved for user-defined purposes

volatile sig_atomic_t sig_received = 0;

extern "C" void signal_handler(int signum) {
    sig_received = signum;
}

void example_signals() {
    std::cout << "\n=== Signals ===\n";

    // Install handler
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, nullptr);

    pid_t pid = fork();

    if (pid == 0) {
        // Child: wait for signal
        std::cout << "  Child waiting for SIGUSR1...\n";
        while (!sig_received) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << "  Child received signal: " << sig_received << "\n";
        _exit(0);
    } else if (pid > 0) {
        // Give child time to start
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "  Parent sending SIGUSR1...\n";
        kill(pid, SIGUSR1);
        waitpid(pid, nullptr, 0);
        std::cout << "  Parent done\n";
    }
}

// CHALLENGE 18.5: Parent sends SIGUSR1 to child, child toggles a flag
// and prints "Child ping". Child then sends SIGUSR1 back to parent,
// parent prints "Parent pong". (Use sigaction for both.)
void challenge_signal_pingpong() {
    std::cout << "\n--- Challenge 18.5: Signal ping-pong ---\n";

    // TODO: Install signal handlers for SIGUSR1 in both processes

    // TODO: fork
    // Child: wait for signal, print "Child ping", send SIGUSR1 to parent
    // Parent: send SIGUSR1 to child, wait for child, print "Parent pong"

    // TODO: waitpid

    std::cout << "Challenge 18.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges

void exercise_ipc() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 18: Inter-Process Communication\n";
    std::cout << "========================================\n";

    example_pipe();
    challenge_pipe();

    example_fifo();
    challenge_fifo();

    example_posix_shm();
    challenge_posix_shm();

    example_boost_shm();
    challenge_boost_shm();

    example_signals();
    challenge_signal_pingpong();

    std::cout << "\n========================================\n";
    std::cout << "IPC exercise complete!\n";
    std::cout << "========================================\n";
}
