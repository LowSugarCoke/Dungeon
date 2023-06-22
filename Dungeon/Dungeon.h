/**
 * @file Dungeon.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief The Dungeon class declaration file.
 *
 * This file contains the declaration of the Dungeon class which acts as the central controller for the game.
 * The Dungeon class manages the game states, scenes, levels, and interactions between different components of the game such as Hero, GameView, GameScene, etc.
 * The class utilizes several other components such as MediaPlayer and DataHandler to manage game sounds and data respectively.
 */

#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include "ui_Dungeon.h"

#include "level.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"
#include "endingScene.h"
#include "mainMenuScene.h"
#include "mediaPlayer.h"
#include "settingScene.h"
#include "introScene.h"
#include "dataHandler.h"

 /**
  * @class Dungeon
  * @brief Main class for the Dungeon game, responsible for managing game states and scenes.
  */
class Dungeon : public QMainWindow
{
    Q_OBJECT

public:

    /**
     * @brief Constructor for the Dungeon class.
     * @param parent Parent widget, default is nullptr.
     */
    Dungeon(QWidget* parent = Q_NULLPTR);

    /**
     * @brief Destructor for the Dungeon class, responsible for freeing allocated memory.
     */
    ~Dungeon();

    /**
     * @brief Proceed to the next level in the game.
     */
    void nextLevel();

    /**
     * @brief Game state when player wins.
     */
    void win();

    /**
     * @brief Game state when player loses.
     */
    void lose();

    /**
     * @brief Enter a battle state in the game.
     */
    void battle();

    /**
     * @brief Show game settings.
     */
    void setting();

    /**
     * @brief Show main menu.
     */
    void menu();

    /**
     * @brief Restart the game.
     */
    void restart();

    /**
     * @brief Show game intro.
     */
    void intro();

    /**
     * @brief Load game data.
     */
    void load();

private:
    Ui::DungeonClass ui; ///< User interface for the Dungeon class.

    Level::LevelElement mCurrentLevel; ///< Current level the player is in.
    std::vector<Level::LevelElement> mLevelData; ///< Data for all game levels.
    Hero* mHero; ///< Player's character.
    GameScene* mGameScene; ///< Main game scene.
    GameView* mSceneView; ///< View for the game scene.
    EndingScene* mEndingScene; ///< Scene displayed at the end of a game.
    MainMenuScene* mMenuScene; ///< Main menu scene.
    SettingScene* mSettingScene; ///< Game settings scene.
    IntroScene* mIntroScene; ///< Game intro scene.
    std::shared_ptr<MediaPlayer> mMediaPlayer; ///< MediaPlayer to manage game sounds.
    std::shared_ptr<DataHandler> mDataHandler; ///< DataHandler to manage game data.
};
