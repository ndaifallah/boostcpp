#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>

// ============================================================
// EXERCISE 6: Boost.Asio Networking
// ============================================================

// CONCEPT: io_context and Basic I/O
// - io_context is the core of Boost.Asio, manages event loop
// - All async operations are tied to an io_context
// - Run the event loop with io_context::run()

void example_io_context() {
    std::cout << "\n=== io_context Example ===\n";

    boost::asio::io_context io;

    std::cout << "io_context created\n";
    std::cout << "Before run, processing...\n";

    // io.run() returns immediately if there's no work
    auto count = io.run();
    std::cout << "Processed " << count << " events\n";

    // Add some work using post()
    std::cout << "Posting 3 tasks:\n";
    boost::asio::post(io, []() { std::cout << "  Task 1 executed\n"; });
    boost::asio::post(io, []() { std::cout << "  Task 2 executed\n"; });
    boost::asio::post(io, []() { std::cout << "  Task 3 executed\n"; });

    count = io.run();
    std::cout << "Processed " << count << " posted tasks\n";
}

// CHALLENGE 6.1: Create an io_context and post 5 tasks that print
// "Task N of 5" where N is 1-5. Run the io_context and verify all execute.
void challenge_io_context() {
    std::cout << "\n--- Challenge 6.1: Posting multiple tasks ---\n";

    // TODO: Create a boost::asio::io_context

    // TODO: Post 5 tasks that each print "Task N of 5 executed"

    // TODO: Run the io_context

    // TODO: Verify that all 5 tasks were processed

    std::cout << "Challenge 6.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: TCP/IP Endpoints and Resolution
// - Resolving hostnames to IP addresses
// - Creating endpoints for connections
// - Querying DNS information

void example_tcp_endpoint() {
    std::cout << "\n=== TCP/IP Endpoint Example ===\n";

    boost::asio::io_context io;

    // Create an endpoint for localhost:8080
    boost::asio::ip::tcp::endpoint localEndpoint(
        boost::asio::ip::address_v4::loopback(), 8080);

    std::cout << "Local endpoint: " << localEndpoint << "\n";
    std::cout << "  Address: " << localEndpoint.address() << "\n";
    std::cout << "  Port: " << localEndpoint.port() << "\n";
    std::cout << "  Is IPv4: " << localEndpoint.address().is_v4() << "\n";

    // DNS resolution
    std::cout << "\nResolving 'localhost':\n";
    boost::asio::ip::tcp::resolver resolver(io);
    boost::asio::ip::tcp::resolver::results_type results =
        resolver.resolve("localhost", "80");

    for (const auto& entry : results) {
        std::cout << "  " << entry.endpoint() << "\n";
    }

    // Resolve google.com (may fail without network)
    std::cout << "\nResolving 'google.com' (may timeout):\n";
    try {
        boost::asio::ip::tcp::resolver::results_type results =
            resolver.resolve("google.com", "443");

        int count = 0;
        for (const auto& entry : results) {
            if (count >= 3) break;
            std::cout << "  " << entry.endpoint() << "\n";
            ++count;
        }
        if (count == 0) {
            std::cout << "  No results (network unavailable)\n";
        }
    } catch (const std::exception& e) {
        std::cout << "  Resolution failed: " << e.what() << "\n";
    }
}

// CHALLENGE 6.2: Create endpoints for common services and display their info
// Create endpoints for: 127.0.0.1:3000, 192.168.1.1:80, ::1:8080 (IPv6)
void challenge_tcp_endpoint() {
    std::cout << "\n--- Challenge 6.2: Creating endpoints ---\n";

    // TODO: Create an io_context

    // TODO: Create TCP endpoint for 127.0.0.1:3000 and print its info

    // TODO: Create TCP endpoint for 192.168.1.1:80 and print its info

    // TODO: Create TCP endpoint for ::1:8080 (IPv6 loopback) and print its info

    // TODO: Create an endpoint using boost::asio::ip::address_v4::any() port 0
    //       and explain what it represents

    std::cout << "Challenge 6.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Timers (Synchronous and Asynchronous)
// - steady_timer for time-based operations
// - Synchronous: wait() blocks until timer expires
// - Asynchronous: async_wait() with callback

void example_timers() {
    std::cout << "\n=== Timer Examples ===\n";

    // Synchronous timer
    std::cout << "\n-- Synchronous Timer --\n";
    boost::asio::io_context io;

    boost::asio::steady_timer timer1(io, std::chrono::milliseconds(500));
    std::cout << "Timer set for 500ms... ";
    std::cout.flush();
    timer1.wait(); // Blocks
    std::cout << "Done!\n";

    // Asynchronous timer
    std::cout << "\n-- Asynchronous Timer --\n";
    boost::asio::steady_timer timer2(io, std::chrono::milliseconds(300));

    std::cout << "Timer set for 300ms (async)... ";
    std::cout.flush();

    bool timerFired = false;
    timer2.async_wait([&timerFired](const boost::system::error_code& ec) {
        if (!ec) {
            timerFired = true;
            std::cout << "Fired!\n";
        }
    });

    std::cout << "Posted, now running io_context... ";
    std::cout.flush();
    io.run();
    std::cout << "io_context finished, timerFired=" << timerFired << "\n";

    // Chain multiple timers
    std::cout << "\n-- Chained Timers --\n";
    boost::asio::io_context io2;
    int counter = 0;

    std::function<void(const boost::system::error_code&)> callback;
    callback = [&counter, &callback, &io2](const boost::system::error_code& ec) {
        if (!ec && counter < 3) {
            std::cout << "  Tick " << (counter + 1) << "\n";
            ++counter;

            auto timer = std::make_shared<boost::asio::steady_timer>(
                io2, std::chrono::milliseconds(200));
            timer->async_wait(callback);
        }
    };

    auto timer3 = std::make_shared<boost::asio::steady_timer>(
        io2, std::chrono::milliseconds(200));
    timer3->async_wait(callback);

    std::cout << "Running chained timers:\n";
    io2.run();
    std::cout << "Finished " << counter << " ticks\n";
}

// CHALLENGE 6.3: Create an async timer that fires 4 times at 100ms intervals
// printing "Tick 1", "Tick 2", "Tick 3", "Tick 4", then "Done!"
void challenge_timers() {
    std::cout << "\n--- Challenge 6.3: Repeating async timer ---\n";

    // TODO: Create an io_context

    // TODO: Create a counter variable starting at 0

    // TODO: Define a callback that:
    //   - Prints "Tick N" where N is counter+1
    //   - Increments counter
    //   - If counter < 4, creates a new timer and calls async_wait recursively
    //   - If counter == 4, prints "Done!"

    // TODO: Create the first timer with 100ms delay and start it

    // TODO: Run the io_context

    std::cout << "Challenge 6.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: TCP Client (Synchronous)
// - Creating a TCP socket
// - Connecting to a server
// - Sending and receiving data
// - Note: This example demonstrates the API, actual connection may fail

void example_tcp_client_concept() {
    std::cout << "\n=== TCP Client Concepts ===\n";

    boost::asio::io_context io;

    // Create a TCP socket
    boost::asio::ip::tcp::socket socket(io);
    std::cout << "TCP socket created\n";
    std::cout << "  Socket is_open: " << socket.is_open() << "\n";

    // Demonstrate endpoint creation (without actually connecting)
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address_v4::loopback(), 9999);

    std::cout << "\nTo connect to a server:\n";
    std::cout << "  1. Create io_context\n";
    std::cout << "  2. Create tcp::socket(io)\n";
    std::cout << "  3. socket.connect(endpoint)  // blocks until connected\n";
    std::cout << "  4. boost::asio::write(socket, boost::asio::buffer(data))\n";
    std::cout << "  5. socket.read_some(boost::asio::buffer(recvBuf))\n";
    std::cout << "  6. socket.close()\n";

    // Example of what a simple echo client would look like:
    std::cout << "\n--- Echo Client Example (pseudocode) ---\n";
    std::cout << "  boost::asio::io_context io;\n";
    std::cout << "  tcp::socket sock(io);\n";
    std::cout << "  sock.connect({ip::address::from_string(\"127.0.0.1\"), 8080});\n";
    std::cout << "  std::string msg = \"Hello Server\\n\";\n";
    std::cout << "  boost::asio::write(sock, boost::asio::buffer(msg));\n";
    std::cout << "  char buf[1024];\n";
    std::cout << "  size_t len = sock.read_some(boost::asio::buffer(buf));\n";
    std::cout << "  std::cout << std::string(buf, len) << std::endl;\n";
}

// CHALLENGE 6.4: Write a function that attempts to connect to a TCP server
// and returns a success/failure status. Use try/catch for error handling.
// (Use a non-existent port so it demonstrates error handling)
void challenge_tcp_client() {
    std::cout << "\n--- Challenge 6.4: TCP connection with error handling ---\n";

    // TODO: Create an io_context and tcp::socket

    // TODO: Try to connect to 127.0.0.1:19999 (likely no server there)

    // TODO: Catch boost::system::system_error and print the error message

    // TODO: If connection succeeds (unlikely), send "Hello" and read response

    // TODO: Close the socket properly in all cases (use RAII or try/finally pattern)

    std::cout << "Challenge 6.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: UDP Sockets
// - Connectionless protocol
// - send_to() and receive() instead of write/read
// - Each message includes sender/receiver endpoint

void example_udp_concepts() {
    std::cout << "\n=== UDP Socket Concepts ===\n";

    boost::asio::io_context io;

    // Create UDP socket
    boost::asio::ip::udp::socket socket(io);
    std::cout << "UDP socket created\n";

    // Open on a specific port
    boost::asio::ip::udp::endpoint localEndpoint(
        boost::asio::ip::address_v4::any(), 0); // Port 0 = let OS choose

    socket.open(boost::asio::ip::udp::v4());
    socket.bind(localEndpoint);

    boost::asio::ip::udp::endpoint actualEndpoint = socket.local_endpoint();
    std::cout << "Bound to: " << actualEndpoint << "\n";

    // UDP endpoint for sending
    boost::asio::ip::udp::endpoint remoteEndpoint(
        boost::asio::ip::address_v4::loopback(), 8888);

    std::cout << "\nTo send UDP:\n";
    std::cout << "  socket.send_to(boost::asio::buffer(data), remoteEndpoint);\n";
    std::cout << "\nTo receive UDP:\n";
    std::cout << "  socket.receive_from(boost::asio::buffer(buf), senderEndpoint);\n";

    socket.close();
    std::cout << "\nUDP socket closed\n";
}

// CHALLENGE 6.5: Create a UDP socket, bind it to a random port,
// then create a send endpoint to localhost:9999.
// Print both endpoints to verify the setup.
void challenge_udp() {
    std::cout << "\n--- Challenge 6.5: UDP socket setup ---\n";

    // TODO: Create an io_context

    // TODO: Create a udp::socket and open it for IPv4

    // TODO: Bind to 0.0.0.0:0 (let OS choose port)

    // TODO: Print the local endpoint (showing the assigned port)

    // TODO: Create a remote endpoint for localhost:9999 and print it

    // TODO: (Optional) Send a test message "ping" to the remote endpoint

    // TODO: Close the socket

    std::cout << "Challenge 6.5 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Async TCP Server Pattern
// - acceptor listens for incoming connections
// - async_accept() handles new clients asynchronously
// - Each client gets its own socket for communication

void example_async_server_pattern() {
    std::cout << "\n=== Async Server Pattern ===\n";

    boost::asio::io_context io;

    // Create an acceptor
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address_v4::loopback(), 0); // Port 0 for demo

    boost::asio::ip::tcp::acceptor acceptor(io, endpoint);

    std::cout << "Acceptor created on: " << acceptor.local_endpoint() << "\n";

    std::cout << "\nServer setup pattern:\n";
    std::cout << "  1. Create io_context\n";
    std::cout << "  2. Create tcp::endpoint(address, port)\n";
    std::cout << "  3. Create tcp::acceptor(io, endpoint)\n";
    std::cout << "  4. Create tcp::socket(io) for accepting\n";
    std::cout << "  5. acceptor.async_accept(socket, callback)\n";
    std::cout << "  6. In callback: handle client, then call async_accept again\n";
    std::cout << "  7. io.run() to start the event loop\n";

    std::cout << "\nClient handling pattern:\n";
    std::cout << "  1. async_read_some() to read data\n";
    std::cout << "  2. Process received data\n";
    std::cout << "  3. async_write() to send response\n";
    std::cout << "  4. Repeat or close connection\n";

    acceptor.close();
}

// CHALLENGE 6.6: Design a simple chat server structure
// Outline the classes and methods needed (no full implementation required)
void challenge_server_design() {
    std::cout << "\n--- Challenge 6.6: Chat server design ---\n";

    // TODO: Define a ChatServer class with:
    //   - io_context member
    //   - tcp::acceptor member
    //   - startAccept() method
    //   - handleAccept() callback

    // TODO: Define a ChatSession class with:
    //   - tcp::socket member
    //   - read buffer
    //   - write queue
    //   - startRead() / handleRead() methods
    //   - startWrite() / handleWrite() methods

    // TODO: Explain how sessions would communicate with each other
    //       (hint: shared message queue or broadcast mechanism)

    // TODO: Explain how you would handle graceful client disconnection

    std::cout << "Challenge 6.6 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_asio_networking() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 6: Boost.Asio Networking\n";
    std::cout << "========================================\n";

    example_io_context();
    challenge_io_context();

    example_tcp_endpoint();
    challenge_tcp_endpoint();

    example_timers();
    challenge_timers();

    example_tcp_client_concept();
    challenge_tcp_client();

    example_udp_concepts();
    challenge_udp();

    example_async_server_pattern();
    challenge_server_design();

    std::cout << "\n========================================\n";
    std::cout << "Boost.Asio Networking exercise complete!\n";
    std::cout << "========================================\n";
}
