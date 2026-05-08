#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>

// ============================================================
// EXERCISE 17: Processes and System Calls
// ============================================================

// CONCEPT: fork()
// - Creates a new process (child) as a copy of the parent
// - Returns child PID to parent, 0 to child, -1 on error
// - Both processes continue executing from the fork() call
// - Use getpid() and getppid() to identify processes

void example_fork_basic() {
    std::cout << "\n=== Basic fork() ===\n";

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "  fork() failed\n";
        return;
    }

    if (pid == 0) {
        // Child process
        std::cout << "  CHILD:  pid=" << getpid()
                  << ", parent pid=" << getppid() << "\n";
        _exit(0);  // child exits
    } else {
        // Parent process
        std::cout << "  PARENT: pid=" << getpid()
                  << ", child pid=" << pid << "\n";
        waitpid(pid, nullptr, 0);  // wait for child
        std::cout << "  PARENT: child has exited\n";
    }
}

// CHALLENGE 17.1: Fork a child process. Parent prints "Parent: <pid>",
// child prints "Child: <pid>". Each prints a message 3 times with 200ms
// delay so you can see interleaving.
void challenge_fork_basic() {
    std::cout << "\n--- Challenge 17.1: Fork and print ---\n";

    // TODO: fork()

    // TODO: if child, loop 3x: print "Child: <pid> iteration N", sleep 200ms

    // TODO: if parent, loop 3x: print "Parent: <pid> iteration N", sleep 200ms

    // TODO: parent calls waitpid() before returning

    std::cout << "Challenge 17.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: exec() family
// - Replaces current process image with a new program
// - execlp(), execvp() search PATH for the executable
// - If exec succeeds, it never returns
// - Typically used after fork() in the child process

void example_exec() {
    std::cout << "\n=== exec() after fork ===\n";

    pid_t pid = fork();

    if (pid == 0) {
        // Child: replace with /bin/ls
        std::cout << "  CHILD: running /bin/ls -l\n";
        execl("/bin/ls", "ls", "-l", nullptr);
        // Only reached if exec fails
        std::cerr << "  CHILD: exec failed\n";
        _exit(1);
    } else if (pid > 0) {
        waitpid(pid, nullptr, 0);
        std::cout << "  PARENT: ls completed\n";
    }
}

// CHALLENGE 17.2: Fork a child that executes "echo Hello from child!"
// using execlp(). Parent waits and prints "Done".
void challenge_exec() {
    std::cout << "\n--- Challenge 17.2: Fork + exec ---\n";

    // TODO: fork()

    // TODO: child calls execlp("echo", "echo", "Hello from child!", (char*)NULL);

    // TODO: if exec fails, perror and _exit

    // TODO: parent calls waitpid and prints "Done"

    std::cout << "Challenge 17.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: waitpid() and process status
// - waitpid(pid, &status, options) waits for a specific child
// - WIFEXITED(status): true if child exited normally
// - WEXITSTATUS(status): child's exit code
// - WIFSIGNALED(status): true if child was killed by signal
// - WTERMSIG(status): signal number that killed child

void example_wait_status() {
    std::cout << "\n=== Process Exit Status ===\n";

    pid_t pid = fork();

    if (pid == 0) {
        // Child exits with code 42
        _exit(42);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            std::cout << "  Child exited with code: "
                      << WEXITSTATUS(status) << "\n";
        }
    }
}

// CHALLENGE 17.3: Fork a child that exits with code 99.
// Parent uses waitpid and checks WIFEXITED/WEXITSTATUS to verify.
void challenge_exit_status() {
    std::cout << "\n--- Challenge 17.3: Check exit status ---\n";

    // TODO: fork()

    // TODO: child _exit(99)

    // TODO: parent: waitpid, WIFEXITED, WEXITSTATUS, print "Exit code: 99"

    std::cout << "Challenge 17.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: system() and popen()
// - system(cmd): runs command in a subshell (blocking)
// - popen(cmd, "r"): runs command, returns FILE* to read output
// - Simpler but less control than fork+exec

void example_system() {
    std::cout << "\n=== system() call ===\n";

    std::cout << "  Running 'echo Hello from system()':\n  ";
    std::cout.flush();
    int ret = system("echo Hello from system()");
    std::cout << "  Return code: " << WEXITSTATUS(ret) << "\n";
}

// CHALLENGE 17.4: Use popen() to run "whoami" and read the output.
// Print "Current user: <username>".
void challenge_popen() {
    std::cout << "\n--- Challenge 17.4: popen ---\n";

    // TODO: FILE* pipe = popen("whoami", "r");

    // TODO: Read the output line into a string (fgets or std::getline via fd)

    // TODO: pclose(pipe), print "Current user: <output>"

    std::cout << "Challenge 17.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges

void exercise_processes() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 17: Processes and System Calls\n";
    std::cout << "========================================\n";

    example_fork_basic();
    challenge_fork_basic();

    example_exec();
    challenge_exec();

    example_wait_status();
    challenge_exit_status();

    example_system();
    challenge_popen();

    std::cout << "\n========================================\n";
    std::cout << "Processes exercise complete!\n";
    std::cout << "========================================\n";
}
