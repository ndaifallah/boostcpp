cmake_minimum_required(VERSION 3.13)
project(MyBoostApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Boost
find_package(Boost REQUIRED)

# Find raylib
find_package(PkgConfig REQUIRED)
pkg_check_modules(RAYLIB REQUIRED raylib)

file(GLOB EXERCISE_SOURCES src/exercises/*.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${EXERCISE_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/src ${RAYLIB_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARIES})
