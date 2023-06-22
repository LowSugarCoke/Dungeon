/**
 * @file dataParser.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the DataHandler class, which is responsible for loading and saving game states.
 */

#pragma once

#include <vector>
#include <string>

#include "history.h"

class DataHandler {
public:

    /**
     * @brief Load a game state from a file.
     *
     * The function reads a file at a given path and constructs a History object from it. This History object
     * encapsulates the state of the game at the time it was saved. The game can then be restored to this state.
     *
     * @param kFilePath The path of the file from which to load the game state.
     * @return A History object representing the state of the game.
     */
    History load(const std::string& kFilePath);

    /**
     * @brief Save a game state to a file.
     *
     * The function takes a History object that represents the current state of the game and writes it to a file.
     * This file can later be read to restore the game to this state. The file is saved in the same directory as
     * the executable.
     *
     * @param kHistory The History object representing the state of the game.
     */
    void save(const History& kHistory);
};
