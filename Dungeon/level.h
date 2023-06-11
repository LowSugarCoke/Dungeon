#pragma once

#include <QString>

namespace Level {

    struct LevelElement {
        QString level;
        int mazeLevel; // more high more difficult
        int monsterCount; // more high more difficult
        int monsterspeed; // more low more quick ( 1000 = 1s)
        int starCount; // more star more difficult
        int potionCount; // more potion more easy
        int trapCount; // more trap more hard
    };

    static const LevelElement kEasy{
        "Easy",
       3, // mazeLevel = 3;
       5,  // monsterCount
       1000, // monsterspeed
       3, // starCount = 3
       2, // potionCount
       1, // trapCount
    };

    static const LevelElement kMedium{
        "Medium",
        4, // mazeLevel = 5;
        10, // monsterCount
        700, // monsterspeed
        5, // starCount = 5
        2, // potionCount
        3, // trapCount
    };

    static const LevelElement kHard{
        "Hard",
        5, // mazeLevel = 8;
        15, //monsterCount
        300, // monsterspeed
        7, // starCount = 7
        1, // potionCount
        5, // trapCount
    };




};
