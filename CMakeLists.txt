cmake_minimum_required(VERSION 3.10)
project(MazeGenerator VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(maze_generator main.cpp)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|MSVC")
    target_compile_options(maze_generator PRIVATE -Wall -Wextra)
endif()