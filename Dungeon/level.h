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
        int superPotionCount; // more super potion more easy
        int dragonCount; // more dragon more hard
        int dragonSpeed; // more low more quick ( 1000 = 1s)
    };

    static const LevelElement kLevel1{
    "1",
   3, // mazeLevel = 3;
   3,  // monsterCount
   1200, // monsterspeed
   1, // starCount = 3
   1, // potionCount
   1, // trapCount
   1, // superPotionCount
   0, // dragonCount
   700, // dragonSpeed
    };

    static const LevelElement kLevel2{
        "2",
       3, // mazeLevel = 3;
       5,  // monsterCount
       1100, // monsterspeed
       2, // starCount = 3
       0, // potionCount
       2, // trapCount
       0, // superPotionCount
       0, // dragonCount
          700, // dragonSpeed
    };

    static const LevelElement kLevel3{
        "3",
        4, // mazeLevel = 5;
        7, // monsterCount
        1000, // monsterspeed
        3, // starCount = 5
        1, // potionCount
        3, // trapCount
        0, // superPotionCount
        0, // dragonCount
           700, // dragonSpeed
    };

    static const LevelElement kLevel4{
        "4",
        4, // mazeLevel = 8;
        9, //monsterCount
        900, // monsterspeed
        4, // starCount = 7
        0, // potionCount
        4, // trapCount
        1, // superPotionCount
        0, // dragonCount
           700, // dragonSpeed
    };

    static const LevelElement kLevel5{
    "5",
    4, // mazeLevel = 8;
    11, //monsterCount
    800, // monsterspeed
    5, // starCount = 7
    1, // potionCount
    4, // trapCount
    1, // superPotionCount
    0, // dragonCount
    700, // dragonSpeed
    };

    static const LevelElement kLevel6{
    "6",
    4, // mazeLevel = 8;
    13, //monsterCount
    700, // monsterspeed
    6, // starCount = 7
    1, // potionCount
    4, // trapCount
    1, // superPotionCount
    1, // dragonCount
    600, // dragonSpeed
    };
    static const LevelElement kLevel7{
    "7",
    4, // mazeLevel = 8;
    15, //monsterCount
    600, // monsterspeed
    5, // starCount = 7
    1, // potionCount
    4, // trapCount
    1, // superPotionCount
    0, // dragonCount
    500, // dragonSpeed
    };
    static const LevelElement kLevel8{
    "8",
    4, // mazeLevel = 8;
    17, //monsterCount
    500, // monsterspeed
    6, // starCount = 7
    1, // potionCount
    5, // trapCount
    1, // superPotionCount
    1, // dragonCount
    400, // dragonSpeed
    };
    static const LevelElement kLevel9{
    "9",
    4, // mazeLevel = 8;
    19, //monsterCount
    500, // monsterspeed
    7, // starCount = 7
    1, // potionCount
    5, // trapCount
    2, // superPotionCount
    1, // dragonCount
    400, // dragonSpeed
    };
    static const LevelElement kLevel10{
    "10",
    4, // mazeLevel = 8;
    20, //monsterCount
    500, // monsterspeed
    8, // starCount = 7
    1, // potionCount
    6, // trapCount
    2, // superPotionCount
    3, // dragonCount
    400, // dragonSpeed
    };
};
