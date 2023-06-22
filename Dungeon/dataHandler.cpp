#include "dataHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>

History DataHandler::load(const std::string& kFilePath) {
    std::ifstream file(kFilePath); // Open the file for reading

    if (!file) {
        throw std::runtime_error("Could not open file: " + kFilePath); // Throw an exception if the file cannot be opened
    }

    History history;
    // Load maze
    for (int i = 0; i < 21; i++) {
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);

        history.maze.push_back(std::vector<int>());
        std::string cell;
        while (std::getline(ss, cell, ',')) { // Use ',' as delimiter
            history.maze.back().push_back(std::stoi(cell));
        }
    }

    // Load entities
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream is(line);
        std::string entity;
        is >> entity;
        if (entity == "Level") {
            is >> history.level;
        }
        else if (entity == "Hero") {
            is >> history.heroPos.first >> history.heroPos.second >> history.heroLife;
        }
        else if (entity == "Monster") {
            int x, y;
            while (is >> x >> y) {
                history.monsterPos.push_back({ x, y });
            }
        }
        else if (entity == "MonsterSpeed") {
            is >> history.monsterSpeed;
        }
        else if (entity == "Dragon") {
            int x, y;
            while (is >> x >> y) {
                history.dragonPos.push_back({ x, y });
            }
        }
        else if (entity == "DragonSpeed") {
            is >> history.dragonSpeed;
        }
        else if (entity == "Collection") {
            int x, y;
            while (is >> x >> y) {
                history.collectionPos.push_back({ x, y });
            }
        }
        else if (entity == "Potion") {
            int x, y;
            while (is >> x >> y) {
                history.potionPos.push_back({ x, y });
            }
        }
        else if (entity == "SuperPotion") {
            int x, y;
            while (is >> x >> y) {
                history.superPotionPos.push_back({ x, y });
            }
        }
        else if (entity == "Trap") {
            int x, y;
            while (is >> x >> y) {
                history.trapPos.push_back({ x, y });
            }
        }
    }

    file.close();

    return history;
}

void DataHandler::save(const History& kHistory) {
    std::string filename = "data.txt";
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    // Save maze
    for (size_t i = 0; i < kHistory.maze[0].size(); i++) {
        for (size_t j = 0; j < kHistory.maze.size(); ++j) {
            file << kHistory.maze[j][i];
            if (j != kHistory.maze.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    // Save level
    file << "Level " << kHistory.level << "\n";

    // Save hero
    file << "Hero " << kHistory.heroPos.first << " " << kHistory.heroPos.second << " " << kHistory.heroLife << "\n";

    // Save monsters
    file << "Monster ";
    for (const auto& monster : kHistory.monsterPos) {
        file << monster.first << " " << monster.second << " ";
    }
    file << "\n";

    // Save MonsterSpeed
    file << "MonsterSpeed " << kHistory.monsterSpeed << "\n";

    // Save dragons
    file << "Dragon ";
    for (const auto& dragon : kHistory.dragonPos) {
        file << dragon.first << " " << dragon.second << " ";
    }
    file << "\n";

    // Save DragonSpeed
    file << "DragonSpeed " << kHistory.dragonSpeed << "\n";

    // Save collections
    file << "Collection ";
    for (const auto& collection : kHistory.collectionPos) {
        file << collection.first << " " << collection.second << " ";
    }
    file << "\n";

    // Save Potion
    file << "Potion ";
    for (const auto& potion : kHistory.potionPos) {
        file << potion.first << " " << potion.second << " ";
    }
    file << "\n";

    // Save super potions
    file << "SuperPotion ";
    for (const auto& superPotion : kHistory.superPotionPos) {
        file << superPotion.first << " " << superPotion.second << " ";
    }
    file << "\n";

    // Save traps
    file << "Trap ";
    for (const auto& trap : kHistory.trapPos) {
        file << trap.first << " " << trap.second << " ";
    }

    file.close();
}
