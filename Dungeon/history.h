/**
 * @file history.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the History struct which stores the historical state of a game.
 * It can be used to save/restore game states, supporting features like undo, replay, etc.
 */

#pragma once

#include <vector>

struct History {
    std::vector<std::vector<int>> maze; // Represents the state of the maze in a 2D vector.
    std::pair<int, int> heroPos; // Represents the position of the hero in the maze.
    int level; // The current level of the game.
    int heroLife; // The current life of the hero.
    std::vector<std::pair<int, int>> monsterPos; // Represents the positions of monsters in the maze.
    int monsterSpeed; // The speed of monsters in the maze.
    std::vector<std::pair<int, int>> dragonPos; // Represents the positions of dragons in the maze.
    int dragonSpeed; // The speed of dragons in the maze.
    std::vector<std::pair<int, int>> collectionPos; // Represents the positions of collectable items in the maze.
    std::vector<std::pair<int, int>> potionPos; // Represents the positions of potions in the maze.
    std::vector<std::pair<int, int>> superPotionPos; // Represents the positions of super potions in the maze.
    std::vector<std::pair<int, int>> trapPos; // Represents the positions of traps in the maze.
};
