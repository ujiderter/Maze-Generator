#include <vector>
#include <random>
#include <iostream>
#include <stack>

class Maze {
private:
    std::vector<std::vector<char>> grid;
    int width, height;
    std::mt19937 rng;

    bool isValid(int x, int y) const {
        return x >= 0 && x < width && y >= 0 && y < height && grid[y][x] == '#';
    }

public:
    Maze(int w, int h) : width(w), height(h), rng(std::random_device{}()) {
        grid.assign(h, std::vector<char>(w, '#'));
    }

    void generateRecursiveBacktracking() {
        std::stack<std::pair<int, int>> stack;
        grid[1][1] = '.';
        stack.emplace(1, 1);

        std::vector<std::pair<int, int>> directions = {
            {0, -2}, {0, 2}, {-2, 0}, {2, 0}
        };

        while (!stack.empty()) {
            auto [x, y] = stack.top();
            std::shuffle(directions.begin(), directions.end(), rng);

            bool found = false;
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (isValid(nx, ny)) {
                    grid[ny][nx] = '.';
                    grid[y + dy/2][x + dx/2] = '.';
                    stack.emplace(nx, ny);
                    found = true;
                    break;
                }
            }
            if (!found) stack.pop();
        }
    }

    void print() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
    }
};

int main() {
    Maze maze(11, 11);
    maze.generateRecursiveBacktracking();
    maze.print();
    return 0;
}