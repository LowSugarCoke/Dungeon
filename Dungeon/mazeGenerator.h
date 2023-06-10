#pragma once
#include <vector>

#include "level.h"

class MazeGenerator {
public:
    MazeGenerator(int width, int height, Difficulty difficulty);

    int operator()(int i, int j) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;
    std::vector<std::vector<int>> maze;
    Difficulty difficulty;
    void DFS();
    int MazeGenerator::getDeadEndProbability();
};
