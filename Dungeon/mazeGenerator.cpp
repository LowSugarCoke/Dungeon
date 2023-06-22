#include "mazeGenerator.h"

#include <algorithm>
#include <ctime>
#include <stack>
#include <vector>
#include <chrono>
#include <random>

MazeGenerator::MazeGenerator(int mWidth, int mHeight, const Level::LevelElement& kLevelElement)
    : mWidth(mWidth * 2 + 1), mHeight(mHeight * 2 + 1),
    mMazeVec(this->mWidth, std::vector<int>(this->mHeight, 1)) {
    do {
        generateMaze(kLevelElement);
    } while (!isConnected());
}

int MazeGenerator::operator()(int i, int j) const {
    return mMazeVec[i][j];
}

int MazeGenerator::getWidth() const {
    return mWidth;
}

int MazeGenerator::getHeight() const {
    return mHeight;
}

std::vector<std::vector<int>>  MazeGenerator::getMaze() {
    return mMazeVec;
}

/**
 * Generates the maze (mMazeVec) based on the provided LevelElement (kLevelElement). The maze is generated
 * by using depth-first search (DFS) and randomization to ensure complexity and solvability.
 *
 * @param kLevelElement The LevelElement to be used in the generation of the maze.
 */
void MazeGenerator::generateMaze(const Level::LevelElement& kLevelElement) {
    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, kLevelElement.mazeLevel);

    // Stack for DFS algorithm and initialization with the starting position
    std::stack<std::pair<int, int>> st;
    st.push({ 2, 2 });

    // Directions of movement in the maze
    std::vector<std::pair<int, int>> dirs = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };

    // DFS loop
    while (!st.empty()) {
        // Current position
        std::pair<int, int> current = st.top();
        st.pop();
        int x = current.first;
        int y = current.second;
        // Mark current cell as visited
        mMazeVec[x][y] = 0;

        // Shuffle the directions to ensure randomness
        std::shuffle(dirs.begin(), dirs.end(), gen);

        // Keep track of valid next cells.
        std::vector<std::pair<int, int>> validNext;

        // Check all possible next cells
        for (auto dir : dirs) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            int mx = (nx + x) / 2;
            int my = (ny + y) / 2;

            // Check if the next cell is within the maze bounds and is unvisited
            if (nx >= 2 && nx < mWidth - 1 && ny >= 2 && ny < mHeight - 1 && mMazeVec[nx][ny] == 1) {
                validNext.push_back({ nx, ny });
                // Mark the cell on the path from the current cell to the next cell as visited
                mMazeVec[mx][my] = 0;
            }
        }

        // Randomly select a next cell and randomly decide whether to create dead-ends.
        if (!validNext.empty()) {
            // Shuffle to ensure randomness
            std::shuffle(validNext.begin(), validNext.end(), gen);

            // If the random variable is less than 3, create another path; otherwise, create a dead-end.
            for (size_t i = 0; i < validNext.size(); ++i) {
                if (i == 0 || dis(gen) < 3) {
                    // The first one is the next cell to visit, or if the random variable is less than 3, create another path.
                    st.push(validNext[i]);
                }
                else {
                    // Others are dead-ends.
                    mMazeVec[validNext[i].first][validNext[i].second] = 0;
                }
            }
        }
    }
}


/**
 * Checks if all parts of the maze (mMazeVec) are connected using depth-first search (DFS).
 * It assumes that all reachable spaces of the maze have a value of 0.
 *
 * @return True if all parts of the maze are reachable from each other, false otherwise.
 */
bool MazeGenerator::isConnected() {
    // Initialize the visited matrix, initially all cells are unvisited
    std::vector<std::vector<bool>> visited(mWidth, std::vector<bool>(mHeight, false));

    // Stack for DFS algorithm and initialization with the starting position
    std::stack<std::pair<int, int>> st;
    st.push({ 2, 2 });

    // DFS loop
    while (!st.empty()) {
        // Current position
        std::pair<int, int> current = st.top();
        st.pop();
        int x = current.first;
        int y = current.second;

        // If the current cell has not been visited
        if (!visited[x][y]) {
            // Mark current cell as visited
            visited[x][y] = true;

            // Directions of movement in the maze
            std::vector<std::pair<int, int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

            // Check all possible next cells
            for (auto dir : dirs) {
                int nx = x + dir.first;
                int ny = y + dir.second;

                // Check if the next cell is within the maze bounds, is reachable, and is unvisited
                if (nx >= 0 && nx < mWidth && ny >= 0 && ny < mHeight && mMazeVec[nx][ny] == 0 && !visited[nx][ny]) {
                    // Push the next cell to the stack
                    st.push({ nx, ny });
                }
            }
        }
    }

    // Iterate over all cells in the maze
    for (int i = 0; i < mWidth; ++i) {
        for (int j = 0; j < mHeight; ++j) {
            // If there is a reachable cell that has not been visited, the maze is not connected
            if (mMazeVec[i][j] == 0 && !visited[i][j]) {
                return false;  // Found an unvisited empty space, the maze is not connected.
            }
        }
    }

    // If all reachable cells have been visited, the maze is connected
    return true;  // All empty spaces are visited, the maze is connected.
}
