# Maze Generator

A console-based maze generator written in C++ that creates random mazes using the Recursive Backtracking algorithm. This is a minimal implementation for the first commit, with plans to add interactive gameplay, file I/O, and more algorithms in future updates.

## Features
- Generates a random maze of specified size (currently 11x11).
- Uses Recursive Backtracking algorithm for maze generation.
- Displays the maze in the console using ASCII characters (`#` for walls, `.` for paths).

## Example Output
```
# # # # # # # # # # #
# . . . # . . . . . #
# # # . # . # # # . #
# . . . . . . . # . #
# . # # # # # . # . #
# . # . . . # . # . #
# . # . # . # . # . #
# . . . # . . . . . #
# # # . # . # # # # #
# . . . . . # . . . #
# # # # # # # # # # #
```

## Prerequisites
- C++17 compatible compiler (e.g., GCC, Clang, MSVC)
- CMake 3.10 or higher
- Make (for Unix-like systems) or equivalent build tool

## Future Plans
- Add interactive player movement (WASD controls).
- Implement additional maze generation algorithms (e.g., Prim's, Kruskal's).
- Support saving/loading mazes to/from files.
- Add traps, treasures, and enemies for a game-like experience.