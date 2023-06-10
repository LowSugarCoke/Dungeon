#pragma once

#include <QString>

namespace Level {

    struct LevelElement {
        QString level;
        int mazeLevel; // more high more difficult
        int monsterCount; // more high more difficult
        int monsterspeed; // more low more quick ( 1000 = 1s)
    };

    static const LevelElement kEasy{
        "Easy",
       3, // mazeLevel = 3;
       5,  // monsterCount
       1000, // monsterspeed
    };

    static const LevelElement kMedium{
        "Medium",
        4, // mazeLevel = 4;
        10, // monsterCount
        700, // monsterspeed
    };

    static const LevelElement kHard{
        "Hard",
        8, // mazeLevel = 8;
        30, //monsterCount
        100, // monsterspeed
    };


};
