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
       1,  // monsterCount
       1000, // monsterspeed
       1, // starCount
       1, // potionCount
       3, // trapCount
    };

    static const LevelElement kMedium{
        "Medium",
        5, // mazeLevel = 4;
        1, // monsterCount
        700, // monsterspeed
        1, // starCount
        2, // potionCount
        3, // trapCount
    };

    static const LevelElement kHard{
        "Hard",
        8, // mazeLevel = 8;
        1, //monsterCount
        300, // monsterspeed
        1, // starCount
        2, // potionCount
        3, // trapCount
    };


};
