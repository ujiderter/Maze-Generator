#ifndef MAZE_RENDERER_H
#define MAZE_RENDERER_H

#include <vector>
#include <functional>

/**
 * @brief Base class for maze visualization
 * 
 * Abstract interface that can be implemented with any graphics library
 * (SFML, SDL, OpenGL, etc.)
 */
class MazeRenderer {
public:
    struct Color {
        unsigned char r, g, b, a;
        Color(unsigned char red = 0, unsigned char green = 0, 
              unsigned char blue = 0, unsigned char alpha = 255)
            : r(red), g(green), b(blue), a(alpha) {}
    };
    
    struct CellState {
        enum Type { WALL, PATH, CURRENT, VISITED, START, END };
        Type type;
        Color color;
    };

protected:
    int windowWidth;
    int windowHeight;
    int cellSize;
    int mazeWidth;
    int mazeHeight;
    
    std::vector<std::vector<CellState>> cellStates;
    
    Color wallColor;
    Color pathColor;
    Color currentColor;
    Color visitedColor;
    Color startColor;
    Color endColor;

public:
    /**
     * @brief Constructor
     * @param mWidth Maze width in cells
     * @param mHeight Maze height in cells
     * @param cSize Cell size in pixels
     */
    MazeRenderer(int mWidth, int mHeight, int cSize = 20)
        : mazeWidth(mWidth), mazeHeight(mHeight), cellSize(cSize),
          windowWidth(mWidth * cSize), windowHeight(mHeight * cSize),
          wallColor(40, 40, 40), pathColor(240, 240, 240),
          currentColor(100, 200, 255), visitedColor(200, 200, 255),
          startColor(100, 255, 100), endColor(255, 100, 100)
    {
        cellStates.resize(mHeight, std::vector<CellState>(mWidth));
        for (int y = 0; y < mHeight; ++y) {
            for (int x = 0; x < mWidth; ++x) {
                cellStates[y][x].type = CellState::WALL;
                cellStates[y][x].color = wallColor;
            }
        }
    }
    
    virtual ~MazeRenderer() = default;
    
    /**
     * @brief Initialize graphics subsystem
     * @return true if successful
     */
    virtual bool initialize() = 0;
    
    /**
     * @brief Check if window should close
     */
    virtual bool shouldClose() const = 0;
    
    /**
     * @brief Process input events
     */
    virtual void processEvents() = 0;
    
    /**
     * @brief Clear the window
     */
    virtual void clear() = 0;
    
    /**
     * @brief Render single frame
     */
    virtual void render() = 0;
    
    /**
     * @brief Display rendered frame
     */
    virtual void display() = 0;
    
    /**
     * @brief Close window and cleanup
     */
    virtual void close() = 0;
    
    /**
     * @brief Set cell state
     */
    void setCellState(int x, int y, CellState::Type type) {
        if (x >= 0 && x < mazeWidth && y >= 0 && y < mazeHeight) {
            cellStates[y][x].type = type;
            cellStates[y][x].color = getColorForType(type);
        }
    }
    
    /**
     * @brief Update cell from maze data
     */
    void updateCell(int x, int y, char cellChar) {
        if (x >= 0 && x < mazeWidth && y >= 0 && y < mazeHeight) {
            CellState::Type type = (cellChar == '#') ? CellState::WALL : CellState::PATH;
            setCellState(x, y, type);
        }
    }
    
    /**
     * @brief Update entire maze
     */
    void updateMaze(const std::vector<std::vector<char>>& grid) {
        for (int y = 0; y < mazeHeight && y < static_cast<int>(grid.size()); ++y) {
            for (int x = 0; x < mazeWidth && x < static_cast<int>(grid[y].size()); ++x) {
                updateCell(x, y, grid[y][x]);
            }
        }
    }
    
    /**
     * @brief Set custom colors
     */
    void setWallColor(Color c) { wallColor = c; }
    void setPathColor(Color c) { pathColor = c; }
    void setCurrentColor(Color c) { currentColor = c; }
    void setVisitedColor(Color c) { visitedColor = c; }
    
    /**
     * @brief Get dimensions
     */
    int getMazeWidth() const { return mazeWidth; }
    int getMazeHeight() const { return mazeHeight; }
    int getCellSize() const { return cellSize; }

protected:
    /**
     * @brief Get color for cell type
     */
    Color getColorForType(CellState::Type type) const {
        switch (type) {
            case CellState::WALL: return wallColor;
            case CellState::PATH: return pathColor;
            case CellState::CURRENT: return currentColor;
            case CellState::VISITED: return visitedColor;
            case CellState::START: return startColor;
            case CellState::END: return endColor;
            default: return wallColor;
        }
    }
};

#endif // MAZE_RENDERER_H