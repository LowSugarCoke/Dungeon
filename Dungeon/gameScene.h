/**
 * @file gameScene.h
 * @author Jack Lee
 * @date 2023.06.23
 *
 * @brief This header file contains the GameScene class that represents the main gameplay scene of the game.
 */

#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>

#include "mazeGenerator.h"
#include "collection.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"
#include "brickItem.h"
#include "monster.h"
#include "trap.h"
#include "potion.h"
#include "superPotion.h"
#include "dragon.h"
#include "history.h"
#include "dataHandler.h"


class GameScene : public QGraphicsScene
{
public:

    /**
     * @brief Constructor for the GameScene class.
     * @param parent The parent QObject. Default is nullptr.
     */
    GameScene(QObject* parent = nullptr);

    /**
     * @brief Set the background image for the game scene.
     * @param kSceneImg The path of the image file.
     */
    void setSceneImg(const QString& kSceneImg);

    /**
     * @brief Generate a random map for the game.
     * @param kBrickImg The image for the brick.
     * @param kLevelElement The elements of the level.
     */
    void generatorRandomMap(const QString& kBrickImg, const Level::LevelElement& kLevelElement);

    /**
     * @brief Update the life text display.
     * @param life The updated life value.
     */
    void updateLifeText(int life);

    /**
     * @brief Update the level text display.
     * @param level The updated level value.
     */
    void updateLevelText(QString level);

    /**
     * @brief Decrease the count of collections.
     */
    void decreaseCollectionCount();

    /**
     * @brief Check if all collections are collected.
     * @return true if all collections are collected, false otherwise.
     */
    bool isAllCollectionsCollected() const;

    /**
     * @brief Proceed to the next level of the game.
     */
    void nextLevel();

    /**
     * @brief Handle the lose condition of the game.
     */
    void lose();

    /**
     * @brief Set the hero of the game.
     * @param mHero The hero object.
     */
    void setHero(Hero* mHero);

    /**
     * @brief Load the game data from history.
     * @param history The history object that contains game data.
     */
    void loadData(History history);

    /**
     * @brief Trigger the loading of the game data.
     */
    void callLoad();

    /**
     * @brief Save the current game data.
     */
    void saveData();

    /**
     * @brief Set the data handler for saving and loading game data.
     * @param dataHandler The data handler object.
     */
    void setDataHanlder(std::shared_ptr<DataHandler> dataHandler);

    /**
     * @brief Set the level of the game.
     * @param kLevel The desired level to be set.
     */
    void setLevel(const int& kLevel);

private:
    // Private member variables
    int mBrickSize;// Save the size of your mMaze cells here
    QGraphicsTextItem* mLifeText;
    QGraphicsTextItem* mLevelText;
    QGraphicsTextItem* mShurtkeyText;
    int mRemainingCollections;
    Hero* mHero;
    int mHeroLife;
    int mMonsterSpeed;
    int mDragonSpeed;
    int mLevel;
    int mOffSetX;
    int mOffSetY;

    QGraphicsPixmapItem* mBackgroundItem; // The background item of the scene
    QGraphicsOpacityEffect* mOpacityEffect; // The opacity effect for the scene
    std::vector<Monster*> mMonsters; // A vector containing all monsters in the scene
    std::vector<Dragon*> mDragons; // A vector containing all dragons in the scene
    std::vector<BrickItem*> mBricks; // A vector containing all bricks in the scene
    std::vector<Collection*> mCollections; // A vector containing all collections in the scene
    std::vector<Trap*> mTraps; // A vector containing all traps in the scene
    std::vector<Potion*> mPotions; // A vector containing all potions in the scene
    std::vector<SuperPotion*> mSuperPotions; // A vector containing all super potions in the scene
    std::vector<std::vector<int>> mMaze; // A 2D vector representing the maze in the scene
    std::shared_ptr<DataHandler> mDataHandler; // A smart pointer to a DataHandler object for managing game data

    void cleanData();
    void generateMaze(const QString& kBrickImg, const Level::LevelElement& kLevelElement);
    void placeHero();
    void placeMonster(int monsterCount, int monsterSpeed);
    void placeDragon(int dragonCount, int dragonSpeed);

    template<typename T>
    void placeItems(std::vector<T*>& items, int count, const QString& imageResource);
    void updateTextAndHero(const Level::LevelElement& kLevelElement);
};
