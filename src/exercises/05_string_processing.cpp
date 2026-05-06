#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <map>
#include <iomanip>

// ============================================================
// EXERCISE 5: String Processing
// ============================================================

// CONCEPT: String Splitting and Joining
// - C++ lacks built-in split/join, but we can build them easily
// - Use std::stringstream for tokenizing
// - Use std::accumulate or manual loops for joining

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

std::string join(const std::vector<std::string>& parts, const std::string& delimiter) {
    std::string result;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) result += delimiter;
        result += parts[i];
    }
    return result;
}

void example_split_join() {
    std::cout << "\n=== String Split & Join Examples ===\n";

    std::string csv = "apple,banana,cherry,date,elderberry";
    auto fruits = split(csv, ',');

    std::cout << "Split CSV:\n";
    for (const auto& fruit : fruits) {
        std::cout << "  - " << fruit << "\n";
    }

    std::string path = "home/user/documents/file.txt";
    auto parts = split(path, '/');
    std::cout << "\nPath components: ";
    for (const auto& part : parts) {
        std::cout << "[" << part << "] ";
    }
    std::cout << "\n";

    std::vector<std::string> words = {"Hello", "World", "from", "C++"};
    std::string joined = join(words, " ");
    std::cout << "Joined: " << joined << "\n";

    std::string rejoined = join(words, "-");
    std::cout << "Joined with '-': " << rejoined << "\n";
}

// CHALLENGE 5.1: Parse a query string like "name=Alice&age=30&city=NYC"
// into a map<string, string> by splitting on '&' then on '='
void challenge_split_join() {
    std::cout << "\n--- Challenge 5.1: Query string parsing ---\n";

    std::string query = "name=Alice&age=30&city=NYC&active=true";

    // TODO: Split the query string on '&' to get key=value pairs

    // TODO: For each pair, split on '=' to separate key and value

    // TODO: Store in a std::map<std::string, std::string>

    // TODO: Print each key-value pair

    // Expected output:
    //   active = true
    //   age = 30
    //   city = NYC
    //   name = Alice

    std::cout << "Challenge 5.1 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: String Transformation
// - Case conversion using std::transform and ::tolower/::toupper
// - Trimming whitespace from strings
// - Replacing substrings

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    if (from.empty()) return str;
    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
    return str;
}

void example_transformations() {
    std::cout << "\n=== String Transformation Examples ===\n";

    std::string text = "  Hello, WORLD!  ";
    std::cout << "Original: '" << text << "'\n";
    std::cout << "Lower:    '" << toLower(text) << "'\n";
    std::cout << "Upper:    '" << toUpper(text) << "'\n";
    std::cout << "Trimmed:  '" << trim(text) << "'\n";
    std::cout << "Trimmed + Lower: '" << toLower(trim(text)) << "'\n";

    std::string url = "https://example.com/old/path";
    std::string updated = replaceAll(url, "old", "new");
    std::cout << "\nOriginal URL: " << url << "\n";
    std::cout << "Updated URL:  " << updated << "\n";

    std::string template_str = "Hello {{name}}, welcome to {{place}}!";
    std::string filled = replaceAll(template_str, "{{name}}", "Alice");
    filled = replaceAll(filled, "{{place}}", "Wonderland");
    std::cout << "Template: " << template_str << "\n";
    std::cout << "Filled:   " << filled << "\n";
}

// CHALLENGE 5.2: Implement a camelCase to snake_case converter
// e.g., "myVariableName" -> "my_variable_name"
// Hint: Insert '_' before each uppercase letter (except the first), then convert to lowercase
void challenge_transformations() {
    std::cout << "\n--- Challenge 5.2: camelCase to snake_case ---\n";

    // TODO: Implement a function that converts camelCase to snake_case
    // "myVariableName" -> "my_variable_name"
    // "HTTPServer" -> "h_t_t_p_server" (each uppercase gets underscore before it)
    // "simple" -> "simple"

    // Test cases to verify:
    std::vector<std::pair<std::string, std::string>> tests = {
        {"myVariableName", "my_variable_name"},
        {"simple", "simple"},
        {"XMLParser", "x_m_l_parser"},
        {"helloWorld", "hello_world"},
    };

    // TODO: Run each test case and print pass/fail

    std::cout << "Challenge 5.2 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: Regular Expressions
// - std::regex for pattern matching
// - std::regex_search, std::regex_match, std::regex_replace
// - Useful for validation, parsing, extraction

void example_regex() {
    std::cout << "\n=== Regex Examples ===\n";

    // Email validation
    std::regex emailPattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    std::vector<std::string> emails = {
        "user@example.com",
        "invalid.email",
        "test.user+tag@domain.org",
        "@missing.com",
    };

    std::cout << "Email validation:\n";
    for (const auto& email : emails) {
        bool valid = std::regex_match(email, emailPattern);
        std::cout << "  " << email << " -> " << (valid ? "VALID" : "INVALID") << "\n";
    }

    // Extract numbers from text
    std::regex numberPattern(R"(\d+)");
    std::string text = "The year is 2024, and there are 365 days, 12 months.";
    std::cout << "\nExtracting numbers from: " << text << "\n";

    auto begin = std::sregex_iterator(text.begin(), text.end(), numberPattern);
    auto end = std::sregex_iterator();

    std::cout << "Found numbers: ";
    for (auto it = begin; it != end; ++it) {
        std::cout << it->str() << " ";
    }
    std::cout << "\n";

    // Regex replace
    std::string phone = "(555) 123-4567";
    std::regex phonePattern(R"(\((\d{3})\)\s*(\d{3})-(\d{4}))");
    std::string formatted = std::regex_replace(phone, phonePattern, "+1-$1-$2-$3");
    std::cout << "\nPhone: " << phone << " -> " << formatted << "\n";
}

// CHALLENGE 5.3: Extract all URLs from an HTML snippet
// URLs are in the format href="http://..." or href="https://..."
void challenge_regex() {
    std::cout << "\n--- Challenge 5.3: Extract URLs from HTML ---\n";

    std::string html = R"(
        <html>
        <body>
        <a href="https://example.com">Home</a>
        <a href="http://old-site.com/page">Old Page</a>
        <a href="https://docs.example.org/api">API Docs</a>
        <p>Not a link: http://not-in-href.com</p>
        <a href="https://secure.example.com/login">Login</a>
        </body>
        </html>
    )";

    // TODO: Create a regex pattern to match href="..." values
    // Pattern should capture the URL inside the quotes

    // TODO: Use std::sregex_iterator to find all matches

    // TODO: Print each extracted URL
    // Expected:
    //   https://example.com
    //   http://old-site.com/page
    //   https://docs.example.org/api
    //   https://secure.example.com/login

    std::cout << "Challenge 5.3 incomplete - fill in the TODOs!\n";
}

// ============================================================
// CONCEPT: String Formatting and Parsing
// - Building formatted strings with std::ostringstream
// - Parsing numeric values from strings
// - Padding and alignment

std::string formatNumber(int value, int width, char fill = '0') {
    std::ostringstream oss;
    oss << std::setfill(fill) << std::setw(width) << value;
    return oss.str();
}

std::string formatTable(const std::vector<std::vector<std::string>>& rows) {
    if (rows.empty()) return "";

    size_t cols = rows[0].size();
    std::vector<size_t> widths(cols, 0);

    for (const auto& row : rows) {
        for (size_t i = 0; i < cols && i < row.size(); ++i) {
            widths[i] = std::max(widths[i], row[i].size());
        }
    }

    std::ostringstream oss;
    for (const auto& row : rows) {
        for (size_t i = 0; i < cols && i < row.size(); ++i) {
            if (i > 0) oss << " | ";
            oss << std::setw(widths[i]) << std::left << row[i];
        }
        oss << "\n";
    }
    return oss.str();
}

void example_formatting() {
    std::cout << "\n=== String Formatting Examples ===\n";

    // Number formatting
    std::cout << "Number formatting:\n";
    std::cout << "  ID: " << formatNumber(42, 5) << "\n";
    std::cout << "  ID: " << formatNumber(7, 5, '-') << "\n";
    std::cout << "  ID: " << formatNumber(1234, 8) << "\n";

    // Table formatting
    std::cout << "\nTable:\n";
    std::vector<std::vector<std::string>> table = {
        {"Name", "Age", "City"},
        {"Alice", "30", "New York"},
        {"Bob", "25", "San Francisco"},
        {"Charlie", "35", "London"},
    };
    std::cout << formatTable(table);

    // Building CSV
    std::ostringstream csv;
    csv << "id,name,score\n";
    csv << "1,Alice,95.5\n";
    csv << "2,Bob,87.3\n";
    csv << "3,Charlie,92.1\n";
    std::cout << "\nCSV output:\n" << csv.str();
}

// CHALLENGE 5.4: Parse a log line in the format:
// "[YYYY-MM-DD HH:MM:SS] LEVEL: message"
// Extract date, time, level, and message into separate strings
void challenge_formatting() {
    std::cout << "\n--- Challenge 5.4: Log line parser ---\n";

    std::string logLine = "[2024-03-15 14:32:07] ERROR: Connection timeout on port 8080";

    // TODO: Parse the log line to extract:
    //   - date: "2024-03-15"
    //   - time: "14:32:07"
    //   - level: "ERROR"
    //   - message: "Connection timeout on port 8080"

    // Hint: You can use string::find, string::substr, or regex

    // TODO: Print each extracted component

    // Test with another log line:
    std::string logLine2 = "[2024-12-25 00:00:01] INFO: System started successfully";
    std::cout << "\nSecond log line: " << logLine2 << "\n";

    // TODO: Parse and print the second log line too

    std::cout << "Challenge 5.4 incomplete - fill in the TODOs!\n";
}

// ============================================================
// Run all examples and challenges for this exercise

void exercise_string_processing() {
    std::cout << "========================================\n";
    std::cout << "EXERCISE 5: String Processing\n";
    std::cout << "========================================\n";

    example_split_join();
    challenge_split_join();

    example_transformations();
    challenge_transformations();

    example_regex();
    challenge_regex();

    example_formatting();
    challenge_formatting();

    std::cout << "\n========================================\n";
    std::cout << "String Processing exercise complete!\n";
    std::cout << "========================================\n";
}
