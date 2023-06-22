/**
 * @file level.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the Level namespace, which includes the
 * definition of the LevelElement structure. This structure encapsulates
 * all elements associated with a level in the game.
 */

#pragma once

#include <string>

namespace Level {
    /**
    * @struct LevelElement
    * @brief Represents a level in the game.
    *
    * This structure contains all the details about a level in the game.
    * Each member variable corresponds to a different aspect of the level.
    */
    struct LevelElement {
        std::string level; ///< The level identifier.
        int mazeLevel; ///< The complexity of the maze. Higher values mean more complexity.
        int monsterCount; ///< The number of monsters in the level. Higher values mean more difficulty.
        int monsterspeed; ///< The speed of the monsters. Lower values mean higher speed (1000 equals 1 second).
        int starCount; ///< The number of stars in the level. Higher values mean more difficulty.
        int potionCount; ///< The number of potions in the level. Higher values mean more ease.
        int trapCount; ///< The number of traps in the level. Higher values mean more difficulty.
        int superPotionCount; ///< The number of super potions in the level. Higher values mean more ease.
        int dragonCount; ///< The number of dragons in the level. Higher values mean more difficulty.
        int dragonSpeed; ///< The speed of the dragons. Lower values mean higher speed (1000 equals 1 second).
    };
};
