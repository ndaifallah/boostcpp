#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

int main() {
    std::string s = "  Boost CMake Example  ";
    boost::trim(s);
    std::cout << "Trimmed: '" << s << "'" << std::endl;
    return 0;
}
