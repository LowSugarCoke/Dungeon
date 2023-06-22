#include "levelParser.h"

#include <fstream>
#include <sstream>

std::vector<Level::LevelElement> LevelParser::parser(const std::string kFilePath) {
    std::ifstream file(kFilePath); // Open the file for reading

    if (!file) {
        throw std::runtime_error("Could not open file: " + kFilePath); // Throw an exception if the file cannot be opened
    }

    std::vector<Level::LevelElement> levels;
    std::string line;
    std::getline(file, line);
    std::getline(file, line);
    while (std::getline(file, line)) { // read the file line by line
        std::istringstream iss(line); // create a string stream of the line

        Level::LevelElement level;
        if (!(iss >> level.level >> level.mazeLevel >> level.monsterCount >> level.monsterspeed >> level.starCount >> level.potionCount >> level.trapCount >> level.superPotionCount >> level.dragonCount >> level.dragonSpeed)) {
            throw std::runtime_error("File format error: " + kFilePath); // Throw an exception if the file format is not correct
        }

        levels.push_back(level); // add the level to the list of levels
    }

    file.close(); // Close the file

    return levels;
}
