#include "mazeGenerator.h"

#include <algorithm>
#include <ctime>
#include <stack>
#include <vector>

MazeGenerator::MazeGenerator(int width, int height)
    : width(width * 2 + 1), height(height * 2 + 1), maze(this->width, std::vector<int>(this->height, 1)) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Seed the random generator
    DFS();
}

int MazeGenerator::operator()(int i, int j) const {
    return maze[i][j];
}

int MazeGenerator::getWidth() const {
    return width;
}

int MazeGenerator::getHeight() const {
    return height;
}

void MazeGenerator::DFS() {
    std::stack<std::pair<int, int>> st;
    st.push({ 2, 2 });

    std::vector<std::pair<int, int>> dirs = { {-2, 0}, {2, 0}, {0, -2}, {0, 2} };

    while (!st.empty()) {
        std::pair<int, int> current = st.top();
        st.pop();
        int x = current.first;
        int y = current.second;
        maze[x][y] = 0;

        std::random_shuffle(dirs.begin(), dirs.end());

        for (auto dir : dirs) {
            int nx = x + dir.first;
            int ny = y + dir.second;
            int mx = (x + nx) / 2;
            int my = (y + ny) / 2;

            if (nx >= 2 && nx < width - 1 && ny >= 2 && ny < height - 1 && maze[nx][ny] == 1) {
                maze[mx][my] = 0;
                st.push({ nx, ny });
            }
        }
    }
}
