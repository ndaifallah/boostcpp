#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <csignal>
#include <functional>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>
#include <iomanip>
#include <unordered_map>

// Terminal color codes
namespace TermColor {
    inline const char* RESET    = "\033[0m";
    inline const char* BOLD     = "\033[1m";
    inline const char* RED      = "\033[31m";
    inline const char* GREEN    = "\033[32m";
    inline const char* YELLOW   = "\033[33m";
    inline const char* BLUE     = "\033[34m";
    inline const char* MAGENTA  = "\033[35m";
    inline const char* CYAN     = "\033[36m";
    inline const char* WHITE    = "\033[37m";
}

// ============================================================
// EXERCISE 12: Signal Handling, IRQ, and DMA Concepts
// ============================================================

// ============================================================
// CONCEPT: POSIX Signal Handling
// - Signals are software interrupts delivered to a process
// - SIGINT (Ctrl+C), SIGTERM, SIGUSR1, SIGUSR2, SIGALRM
// - Use signal() or sigaction() to register handlers
// - Signal handlers should be minimal (async-signal-safe)
// - std::atomic<bool> is safe to use in signal handlers

static std::atomic<bool> g_signalReceived{false};
static std::atomic<int> g_signalCount{0};
static std::atomic<int> g_lastSignal{0};

void signalHandler(int signum) {
    g_signalReceived = true;
    g_signalCount++;
    g_lastSignal = signum;
}

void example_signal_handling() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Signal Handling ===" << TermColor::RESET << "\n";

    std::cout << "Common POSIX signals:\n";
    std::cout << "  " << TermColor::RED << "SIGINT  (2)" << TermColor::RESET
              << "  - Interrupt (Ctrl+C)\n";
    std::cout << "  " << TermColor::YELLOW << "SIGTERM (15)" << TermColor::RESET
              << " - Termination request\n";
    std::cout << "  " << TermColor::MAGENTA << "SIGUSR1 (10)" << TermColor::RESET
              << " - User-defined signal 1\n";
    std::cout << "  " << TermColor::MAGENTA << "SIGUSR2 (12)" << TermColor::RESET
              << " - User-defined signal 2\n";
    std::cout << "  " << TermColor::CYAN << "SIGALRM (14)" << TermColor::RESET
              << " - Alarm clock\n";

    // Register a handler for SIGUSR1 (won't actually receive it in this demo)
    std::signal(SIGUSR1, signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::cout << "\nRegistered handlers for SIGUSR1 and SIGTERM\n";
    std::cout << "To send a signal from another terminal:\n";
    std::cout << "  kill -USR1 <pid>   (user-defined signal 1)\n";
    std::cout << "  kill -TERM <pid>   (termination request)\n";
    std::cout << "  kill -INT <pid>    (interrupt/Ctrl+C)\n";
}

// CHALLENGE 12.1: Write a program structure that:
// - Registers handlers for SIGINT, SIGTERM, and SIGUSR1
// - Uses an atomic flag to track if SIGINT was received
// - In a loop, checks the flag and prints status every second
// - Exits cleanly on SIGTERM
void challenge_signal_handling() {
    std::cout << "\n--- Challenge 12.1: Signal handler structure ---\n";

    // TODO: Define atomic<bool> flags for sigintReceived, sigtermReceived, sigusr1Received

    // TODO: Define signal handlers that set the appropriate flags

    // TODO: Register all three signal handlers

    // TODO: Write a loop that:
    //   - Sleeps 1 second
    //   - Checks each flag and prints which signal was received
    //   - Breaks on SIGTERM

    // TODO: Print cleanup message on exit

    std::cout << "Challenge 12.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Software Signal Simulation
// - Simulating signal dispatch in user-space
// - Event-driven pattern similar to hardware interrupts
// - Callback registry and dispatch mechanism

class SignalDispatcher {
public:
    using Handler = std::function<void(int)>;

    void registerHandler(int signal, Handler handler) {
        handlers_[signal] = std::move(handler);
    }

    void dispatch(int signal) {
        if (handlers_.count(signal)) {
            handlers_[signal](signal);
        }
    }

    void dispatchAll() {
        for (auto& [sig, handler] : handlers_) {
            handler(sig);
        }
    }

private:
    std::unordered_map<int, Handler> handlers_;
};

void example_signal_dispatch() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Signal Dispatch Simulation ===" << TermColor::RESET << "\n";

    SignalDispatcher dispatcher;

    dispatcher.registerHandler(1, [](int s) {
        std::cout << "  [" << TermColor::RED << "SIGHUP" << TermColor::RESET
                  << "] Hangup detected, reloading config\n";
    });
    dispatcher.registerHandler(2, [](int s) {
        std::cout << "  [" << TermColor::YELLOW << "SIGINT" << TermColor::RESET
                  << "] Interrupt received, graceful shutdown\n";
    });
    dispatcher.registerHandler(10, [](int s) {
        std::cout << "  [" << TermColor::MAGENTA << "SIGUSR1" << TermColor::RESET
                  << "] User signal 1, rotating logs\n";
    });
    dispatcher.registerHandler(15, [](int s) {
        std::cout << "  [" << TermColor::RED << "SIGTERM" << TermColor::RESET
                  << "] Termination request, saving state\n";
    });

    std::cout << "Simulating signal delivery:\n";
    dispatcher.dispatch(1);
    dispatcher.dispatch(10);
    dispatcher.dispatch(2);
    dispatcher.dispatch(15);
}

// CHALLENGE 12.2: Create a SignalDispatcher and register handlers for:
// - Signal 12 (SIGUSR2): print "Backup triggered"
// - Signal 14 (SIGALRM): print "Timeout warning"
// - Signal 3 (SIGQUIT): print "Core dump requested"
// Dispatch signals 14, 12, 3 in that order.
void challenge_signal_dispatch() {
    std::cout << "\n--- Challenge 12.2: Custom signal dispatcher ---\n";

    // TODO: Create a SignalDispatcher

    // TODO: Register handler for signal 12: print "Backup triggered"

    // TODO: Register handler for signal 14: print "Timeout warning"

    // TODO: Register handler for signal 3: print "Core dump requested"

    // TODO: Dispatch signals 14, 12, 3 in order

    std::cout << "Challenge 12.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: IRQ (Interrupt Request) Handling
// - IRQs are hardware signals sent to the CPU
// - Each device has an IRQ line (IRQ 0-15 on legacy systems)
// - CPU saves state, executes ISR (Interrupt Service Routine), restores state
// - Cannot be directly handled in user-space C++
// - Simulated here to show the pattern

enum IRQLine : int {
    IRQ_TIMER      = 0,
    IRQ_KEYBOARD   = 1,
    IRQ_SERIAL1    = 4,
    IRQ_PARALLEL   = 7,
    IRQ_RTC        = 8,
    IRQ_NETWORK    = 11,
    IRQ_SATA       = 14,
    IRQ_GPU        = 15
};

struct IRQHandler {
    int irqNumber;
    std::string deviceName;
    std::function<void()> serviceRoutine;
    int invocationCount = 0;
};

class IRQController {
public:
    void registerIRQ(int irq, const std::string& device, std::function<void()> routine) {
        IRQHandler handler;
        handler.irqNumber = irq;
        handler.deviceName = device;
        handler.serviceRoutine = std::move(routine);
        irqTable_[irq] = handler;
        std::cout << "  Registered IRQ " << irq << " -> " << device << "\n";
    }

    void triggerIRQ(int irq) {
        if (irqTable_.count(irq)) {
            auto& handler = irqTable_[irq];
            std::cout << "  " << TermColor::YELLOW << "[IRQ " << irq << "]"
                      << TermColor::RESET << " " << handler.deviceName << " requesting service\n";
            handler.serviceRoutine();
            handler.invocationCount++;
        } else {
            std::cout << "  " << TermColor::RED << "[IRQ " << irq << "] Unregistered IRQ!"
                      << TermColor::RESET << "\n";
        }
    }

    void printIRQTable() const {
        std::cout << TermColor::BOLD << "\nIRQ Table:\n" << TermColor::RESET;
        std::cout << std::left << std::setw(6) << "IRQ"
                  << std::setw(16) << "Device"
                  << std::setw(8) << "Calls" << "\n";
        std::cout << std::string(30, '-') << "\n";
        for (const auto& [irq, handler] : irqTable_) {
            std::cout << std::left << std::setw(6) << handler.irqNumber
                      << std::setw(16) << handler.deviceName
                      << std::setw(8) << handler.invocationCount << "\n";
        }
    }

private:
    std::unordered_map<int, IRQHandler> irqTable_;
};

void example_irq_handling() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== IRQ (Interrupt Request) Handling ===" << TermColor::RESET << "\n";

    std::cout << "Common IRQ assignments:\n";
    std::cout << "  IRQ 0  - System Timer\n";
    std::cout << "  IRQ 1  - Keyboard\n";
    std::cout << "  IRQ 4  - Serial Port 1\n";
    std::cout << "  IRQ 7  - Parallel Port\n";
    std::cout << "  IRQ 8  - Real-Time Clock\n";
    std::cout << "  IRQ 11 - Network Controller\n";
    std::cout << "  IRQ 14 - SATA Controller\n";
    std::cout << "  IRQ 15 - GPU\n";

    IRQController pic;

    std::cout << "\nRegistering devices:\n";
    pic.registerIRQ(IRQ_TIMER, "System Timer", []() {
        std::cout << "    [ISR] Timer tick, incrementing jiffies\n";
    });
    pic.registerIRQ(IRQ_KEYBOARD, "Keyboard", []() {
        std::cout << "    [ISR] Key pressed, reading scancode from port 0x60\n";
    });
    pic.registerIRQ(IRQ_NETWORK, "Ethernet", []() {
        std::cout << "    [ISR] Packet received, DMA to ring buffer\n";
    });
    pic.registerIRQ(IRQ_GPU, "GPU", []() {
        std::cout << "    [ISR] VBlank interrupt, swapping frame buffers\n";
    });

    std::cout << "\nSimulating hardware interrupts:\n";
    pic.triggerIRQ(IRQ_TIMER);
    pic.triggerIRQ(IRQ_KEYBOARD);
    pic.triggerIRQ(IRQ_NETWORK);
    pic.triggerIRQ(IRQ_GPU);
    pic.triggerIRQ(IRQ_TIMER);

    pic.printIRQTable();
}

// CHALLENGE 12.3: Create an IRQController and register:
// - IRQ 0 (Timer): increment a counter variable
// - IRQ 1 (Keyboard): print the key code from a simulated port read
// - IRQ 14 (SATA): print "Disk I/O complete"
// Trigger: Timer, SATA, Keyboard, Timer, Timer
// Print the IRQ table showing invocation counts.
void challenge_irq_handling() {
    std::cout << "\n--- Challenge 12.3: Custom IRQ setup ---\n";

    // TODO: Create an IRQController

    // TODO: Register IRQ 0 (Timer) with a counter increment

    // TODO: Register IRQ 1 (Keyboard) with simulated scancode read

    // TODO: Register IRQ 14 (SATA) with disk I/O message

    // TODO: Trigger interrupts: Timer, SATA, Keyboard, Timer, Timer

    // TODO: Print the IRQ table

    std::cout << "Challenge 12.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: DMA (Direct Memory Access)
// - DMA allows hardware to access memory without CPU intervention
// - DMA controller takes over the bus (cycle stealing)
// - Used for disk I/O, network cards, audio, GPU transfers
// - Buffer must be properly aligned and non-pageable
// - Cannot directly use DMA in user-space, but pattern is simulated

struct DMABuffer {
    void* buffer;
    size_t size;
    bool inUse;

    DMABuffer(size_t sz) : size(sz), inUse(false) {
        // In real DMA: buffer must be physically contiguous and aligned
        buffer = std::aligned_alloc(4096, (sz + 4095) & ~4095);
        std::memset(buffer, 0, (sz + 4095) & ~4095);
    }

    ~DMABuffer() { std::free(buffer); }

    DMABuffer(const DMABuffer&) = delete;
    DMABuffer& operator=(const DMABuffer&) = delete;
};

class DMAController {
public:
    explicit DMAController(int channelCount = 8) : channelCount_(channelCount) {
        channels_.resize(channelCount);
    }

    int allocateChannel(size_t bufferSize) {
        for (int i = 0; i < channelCount_; ++i) {
            if (!channels_[i]) {
                channels_[i] = std::make_unique<DMABuffer>(bufferSize);
                channels_[i]->inUse = true;
                std::cout << "  DMA Channel " << i << " allocated ("
                          << bufferSize << " bytes, aligned to 4KB)\n";
                return i;
            }
        }
        return -1;
    }

    void simulateTransfer(int channel, const std::string& direction, size_t bytes) {
        if (channel < 0 || channel >= channelCount_ || !channels_[channel]) {
            std::cout << "  " << TermColor::RED << "[DMA] Invalid channel "
                      << channel << TermColor::RESET << "\n";
            return;
        }
        auto& buf = channels_[channel];
        std::cout << "  " << TermColor::CYAN << "[DMA Ch" << channel << "]"
                  << TermColor::RESET << " " << direction << " " << bytes
                  << " bytes (buffer: " << buf->buffer << ")\n";
    }

    void releaseChannel(int channel) {
        if (channel >= 0 && channel < channelCount_ && channels_[channel]) {
            channels_[channel]->inUse = false;
            channels_[channel].reset();
            std::cout << "  DMA Channel " << channel << " released\n";
        }
    }

private:
    int channelCount_;
    std::vector<std::unique_ptr<DMABuffer>> channels_;
};

void example_dma_handling() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== DMA (Direct Memory Access) ===" << TermColor::RESET << "\n";

    std::cout << "DMA concepts:\n";
    std::cout << "  - Hardware transfers data directly to/from memory\n";
    std::cout << "  - CPU is free to do other work during transfer\n";
    std::cout << "  - Requires physically contiguous, aligned buffers\n";
    std::cout << "  - Common channels: disk, network, audio, USB\n";
    std::cout << "  - Transfer modes: single, block, demand, cascade\n";

    DMAController dma;

    std::cout << "\nAllocating DMA channels:\n";
    int diskChannel = dma.allocateChannel(65536);   // 64KB for disk read
    int netChannel  = dma.allocateChannel(16384);   // 16KB for network
    int audioChannel = dma.allocateChannel(8192);   // 8KB for audio

    std::cout << "\nSimulating DMA transfers:\n";
    dma.simulateTransfer(diskChannel, "READ from disk to memory", 65536);
    dma.simulateTransfer(netChannel, "WRITE from memory to NIC", 8192);
    dma.simulateTransfer(audioChannel, "READ from memory to DAC", 4096);
    dma.simulateTransfer(diskChannel, "READ from disk to memory", 32768);

    std::cout << "\nReleasing channels:\n";
    dma.releaseChannel(diskChannel);
    dma.releaseChannel(netChannel);
    dma.releaseChannel(audioChannel);
}

// CHALLENGE 12.4: Create a DMAController with 4 channels.
// Allocate channels for: GPU transfer (32KB), USB transfer (4KB), and SATA (64KB).
// Simulate: GPU write, SATA read, USB read, GPU write, SATA read.
// Release all channels.
void challenge_dma_handling() {
    std::cout << "\n--- Challenge 12.4: Custom DMA transfers ---\n";

    // TODO: Create DMAController with 4 channels

    // TODO: Allocate channel for GPU (32KB)

    // TODO: Allocate channel for USB (4KB)

    // TODO: Allocate channel for SATA (64KB)

    // TODO: Simulate transfers: GPU write, SATA read, USB read, GPU write, SATA read

    // TODO: Release all channels

    std::cout << "Challenge 12.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Combined IRQ + DMA Pattern
// - Real hardware: device raises IRQ when DMA transfer completes
// - ISR checks DMA status and signals waiting process
// - This is how disk I/O, network packets, and audio work

void example_irq_dma_combined() {
    std::cout << "\n" << TermColor::GREEN << TermColor::BOLD
              << "=== Combined IRQ + DMA Pattern ===" << TermColor::RESET << "\n";

    std::atomic<bool> transferComplete{false};

    DMAController dma;
    int diskCh = dma.allocateChannel(4096);

    IRQController pic;
    pic.registerIRQ(IRQ_SATA, "SATA Controller", [&transferComplete]() {
        std::cout << "    [SATA ISR] DMA transfer complete, setting flag\n";
        transferComplete = true;
    });

    std::cout << "\nSimulating disk read:\n";
    std::cout << "  1. CPU programs DMA controller with buffer address and size\n";
    dma.simulateTransfer(diskCh, "READ (initiated)", 4096);

    std::cout << "  2. CPU continues other work (not blocked!)\n";
    std::cout << "     CPU: processing other tasks...\n";

    std::cout << "  3. DMA transfers data in background\n";

    std::cout << "  4. Device raises IRQ when DMA finishes\n";
    pic.triggerIRQ(IRQ_SATA);

    std::cout << "  5. ISR sets completion flag, waiting thread resumes\n";
    std::cout << "  transferComplete = " << (transferComplete ? "true" : "false") << "\n";

    dma.releaseChannel(diskCh);
}

// CHALLENGE 12.5: Simulate a network card receiving a packet:
// - Allocate DMA channel for network (16KB)
// - Register IRQ handler for IRQ_NETWORK that sets a "packetReady" flag
// - Simulate: DMA transfer "packet from NIC to memory"
// - Trigger IRQ_NETWORK
// - Check packetReady flag and print "Packet processed"
void challenge_irq_dma_combined() {
    std::cout << "\n--- Challenge 12.5: Network packet reception ---\n";

    // TODO: Create atomic<bool> packetReady = false

    // TODO: Create DMAController and allocate channel for network (16KB)

    // TODO: Create IRQController and register IRQ_NETWORK handler

    // TODO: Simulate DMA transfer "packet from NIC to memory"

    // TODO: Trigger IRQ_NETWORK

    // TODO: Check packetReady flag and print result

    // TODO: Release DMA channel

    std::cout << "Challenge 12.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_systems_hardware() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 12: Signals, IRQ, and DMA\n";
    std::cout << "========================================\n";

    example_signal_handling();
    challenge_signal_handling();

    example_signal_dispatch();
    challenge_signal_dispatch();

    example_irq_handling();
    challenge_irq_handling();

    example_dma_handling();
    challenge_dma_handling();

    example_irq_dma_combined();
    challenge_irq_dma_combined();

    std::cout << "\n========================================\n";
    std::cout << "Systems and Hardware exercise complete!\n";
    std::cout << "========================================\n";
}
