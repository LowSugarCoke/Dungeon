/**
 * @file levelParser.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the LevelParser class. It is responsible for
 * parsing a given file and returning a vector of LevelElement instances.
 * The LevelElement instances correspond to the levels described in the file.
 */

#pragma once

#include <vector>
#include <string>

#include "level.h"

class LevelParser {
public:

    /**
     * Parses a file to generate a vector of LevelElement instances.
     *
     * @param kFilePath: The path to the file to be parsed.
     * @return A vector of LevelElement instances. Each instance corresponds to a level
     * described in the file. The order of instances in the vector corresponds to the order
     * of levels in the file.
     * @throws std::runtime_error if the file cannot be opened or its format is not correct.
     */
    std::vector<Level::LevelElement> parser(const std::string kFilePath);
};
