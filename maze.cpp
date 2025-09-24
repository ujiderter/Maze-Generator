#include <vector>
#include <random>
#include <iostream>
#include <stack>
#include <fstream>
#include <string>

/**
 * @brief A maze generator using recursive backtracking algorithm
 * 
 * This class creates random mazes using the recursive backtracking algorithm.
 * The maze is represented as a 2D grid where '#' represents walls and '.' represents paths.
 */
class Maze {
private:
    std::vector<std::vector<char>> grid;
    int width, height;
    std::mt19937 rng;
    
    /**
     * @brief Check if coordinates are valid and point to a wall
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if valid wall position, false otherwise
     */
    bool isValid(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height && grid[y][x] == '#';
    }

public:
    /**
     * @brief Construct a new Maze object
     * @param w Width of the maze (should be odd for proper generation)
     * @param h Height of the maze (should be odd for proper generation)
     */
    Maze(int w, int h) : width(w), height(h), rng(std::random_device{}()) {
        // Initialize grid with walls
        grid.assign(h, std::vector<char>(w, '#'));
    }
    
    /**
     * @brief Generate maze using recursive backtracking algorithm
     * 
     * This algorithm creates a perfect maze (no loops, exactly one path between any two points)
     */
    void generateRecursiveBacktracking() {
        std::stack<std::pair<int, int>> stack;
        
        // Start from position (1,1)
        grid[1][1] = '.';
        stack.emplace(1, 1);
        
        // Four possible directions (up, down, left, right) with step of 2
        std::vector<std::pair<int, int>> directions = {
            {0, -2}, {0, 2}, {-2, 0}, {2, 0}  // up, down, left, right
        };
        
        while (!stack.empty()) {
            auto [x, y] = stack.top();
            
            // Randomize direction order
            std::shuffle(directions.begin(), directions.end(), rng);
            
            bool found = false;
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                
                // Check if we can move to this position
                if (isValid(nx, ny)) {
                    // Carve path to new position
                    grid[ny][nx] = '.';
                    // Carve path between current and new position
                    grid[y + dy/2][x + dx/2] = '.';
                    
                    // Add new position to stack
                    stack.emplace(nx, ny);
                    found = true;
                    break;
                }
            }
            
            // If no valid moves, backtrack
            if (!found) {
                stack.pop();
            }
        }
    }
    
    /**
     * @brief Print the maze to console
     */
    void print() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
    }
    
    /**
     * @brief Save maze to file
     * @param filename Name of the output file
     * @return true if successful, false otherwise
     */
    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        for (const auto& row : grid) {
            for (char cell : row) {
                file << cell << ' ';
            }
            file << '\n';
        }
        
        file.close();
        return true;
    }
    
    /**
     * @brief Get maze dimensions
     * @return pair of (width, height)
     */
    std::pair<int, int> getDimensions() const {
        return {width, height};
    }
    
    /**
     * @brief Check if position is a path (not a wall)
     * @param x X coordinate
     * @param y Y coordinate
     * @return true if position is a path, false if wall or out of bounds
     */
    bool isPath(int x, int y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return false;
        }
        return grid[y][x] == '.';
    }
};