/**
 * @file resource.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the file paths for different types of resources required for the game.
 * These resources are categorized under different namespaces, UIResource, DataResource, and MusicResource.
 */

#pragma once

#include <QString>

 // This namespace contains the paths to the image resources used in the game UI
namespace UIResource {
    const static QString kSceneImg = "Resources\\img\\scene.jpg";
    const static QString kBrickImg = "Resources\\img\\brick.jfif";
    const static QString kHero = "Resources\\img\\hero.png";
    const static QString kMonster = "Resources\\img\\monster.png";
    const static QString kStar = "Resources\\img\\star.png";
    const static QString kPotion = "Resources\\img\\potion.png";
    const static QString kSuperPotion = "Resources\\img\\super-potion.png";
    const static QString kTrap = "Resources\\img\\trap.png";
    const static QString kWin = "Resources\\img\\win.jfif";
    const static QString kLose = "Resources\\img\\lose.jpg";
    const static QString kButton = "Resources\\img\\button.png";
    const static QString kMenu = "Resources\\img\\menu.jpg";
    const static QString kDragon = "Resources\\img\\dragon.png";
    const static QString kLogo = "Resources\\img\\logo.png";
    const static QString kExclamationMark = "Resources\\img\\exclamationMark.png";
    const static QString kTitle = "Resources\\img\\title.png";
}

// This namespace contains the paths to the data files used in the game
namespace DataResource {
    const static QString kLevel = "level.txt";
    const static QString kData = "data.txt";
}

// This namespace contains the paths to the music files used in the game
namespace MusicResource {
    const static QString kPotion = "Resources\\mp3\\potion.mp3";
    const static QString kSuperPotion = "Resources\\mp3\\superPotion.mp3";
    const static QString kCollection = "Resources\\mp3\\collection.mp3";
    const static QString kMonster = "Resources\\mp3\\monster.mp3";
    const static QString kNextLevel = "Resources\\mp3\\nextLevel.mp3";
    const static QString kTrap = "Resources\\mp3\\trap.mp3";
    const static QString kMainMenu = "Resources\\mp3\\menu.mp3";
    const static QString kEndingWin = "Resources\\mp3\\win.mp3";
    const static QString kEndingLose = "Resources\\mp3\\lose.mp3";
    const static QString kDragon = "Resources\\mp3\\dragon.mp3";
    const static QString kBattle = "Resources\\mp3\\battle.mp3";
}
