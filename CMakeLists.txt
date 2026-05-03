cmake_minimum_required(VERSION 3.12)
project(MyBoostApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Boost
find_package(Boost REQUIRED)

file(GLOB EXERCISE_SOURCES src/exercises/*.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${EXERCISE_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src)
# For header-only Boost components, no linking is necessary.
# If you use compiled Boost libraries, link them here, e.g.:
# target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)
