#pragma once
#include <vector>

class MazeGenerator {
public:
    MazeGenerator(int width, int height);

    int operator()(int i, int j) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
    std::vector<std::vector<int>> maze;

    void DFS();
};
