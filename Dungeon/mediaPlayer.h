/**
 * @file mediaPlayer.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This header file contains the MediaPlayer class, which manages all the media used in the game.
 */

#pragma once

#include <memory>

#include <QMediaPlayer>

class MediaPlayer {
public:

    /**
     * @brief Default constructor. It initializes all the media players.
     */
    MediaPlayer();

    std::shared_ptr<QMediaPlayer> potion;        // Media player for potion sound effects
    std::shared_ptr<QMediaPlayer> superPotion;   // Media player for super potion sound effects
    std::shared_ptr<QMediaPlayer> collection;    // Media player for collection sound effects
    std::shared_ptr<QMediaPlayer> monster;       // Media player for monster sound effects
    std::shared_ptr<QMediaPlayer> nextLevel;     // Media player for next level sound effects
    std::shared_ptr<QMediaPlayer> trap;          // Media player for trap sound effects
    std::shared_ptr<QMediaPlayer> mainMenu;      // Media player for main menu sound track
    std::shared_ptr<QMediaPlayer> start;         // Media player for start game sound effects
    std::shared_ptr<QMediaPlayer> battle;        // Media player for battle sound effects
    std::shared_ptr<QMediaPlayer> endingWin;     // Media player for win game sound effects
    std::shared_ptr<QMediaPlayer> endingLose;    // Media player for lose game sound effects
};
