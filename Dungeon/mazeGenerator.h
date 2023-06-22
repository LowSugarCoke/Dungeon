/**
 * @file mazeGenerator.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the MazeGenerator class, which is used for generating
 * a maze (mMazeVec) of a specified width (mWidth) and height (mHeight). The mMazeVec is represented as a 2D vector
 * where each cell represents a tile in the maze. The mMazeVec is randomly generated
 * upon creation of the MazeGenerator object, ensuring that all parts of the maze
 * are reachable.
 */

#pragma once
#include <vector>
#include <memory>

#include "level.h"

class MazeGenerator {
public:
    /**
     * Constructor for the MazeGenerator class.
     *
     * @param mWidth The width of the maze (mMazeVec) to be generated.
     * @param mHeight The height of the maze (mMazeVec) to be generated.
     * @param kLevelElement A LevelElement object to be used in the maze generation process.
     */
    MazeGenerator(int mWidth, int mHeight, const Level::LevelElement& kLevelElement);

    /**
     * Overloaded operator() to return the element of mMazeVec at a specific coordinate.
     *
     * @param i The x-coordinate (row) of the desired element.
     * @param j The y-coordinate (column) of the desired element.
     * @return The element of mMazeVec at the specified coordinates.
     */
    int operator()(int i, int j) const;

    /**
     * Getter for the width (mWidth) of the maze (mMazeVec).
     *
     * @return The width of the maze.
     */
    int getWidth() const;

    /**
     * Getter for the height (mHeight) of the maze (mMazeVec).
     *
     * @return The height of the maze.
     */
    int getHeight() const;

    /**
     * Getter for the 2D vector representing the maze (mMazeVec).
     *
     * @return The 2D vector representing the maze.
     */
    std::vector<std::vector<int>>  getMaze();

private:
    int mWidth;
    int mHeight;
    std::vector<std::vector<int>> mMazeVec;

    /**
     * Checks if all parts of the maze (mMazeVec) are connected.
     *
     * @return True if all parts of the maze are reachable from each other, false otherwise.
     */
    bool isConnected();

    /**
     * Generates the maze (mMazeVec) based on the provided LevelElement (kLevelElement).
     *
     * @param kLevelElement The LevelElement to be used in the generation of the maze.
     */
    void generateMaze(const Level::LevelElement& kLevelElement);
};
