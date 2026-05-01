cmake_minimum_required(VERSION 3.12)
project(MyBoostApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Boost
find_package(Boost REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
# For header-only Boost components, no linking is necessary.
# If you use compiled Boost libraries, link them here, e.g.:
# target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
