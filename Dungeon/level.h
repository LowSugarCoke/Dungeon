#pragma once
namespace Level {

    struct LevelElement {
        int mazeLevel; // more high more difficult
        int monsterCount;
        int monsterspeed; // more low more quick ( 1000 = 1s)
    };

    static const LevelElement kEasy{
       3, // mazeLevel = 3;
       5,  // monsterCount
       1000, // monsterspeed
    };

    static const LevelElement kMedium{
        4, // mazeLevel = 4;
        10, // monsterCount
        700, // monsterspeed
    };

    static const LevelElement kHard{
        8, // mazeLevel = 8;
        15, //monsterCount
        300, // monsterspeed
    };


};
