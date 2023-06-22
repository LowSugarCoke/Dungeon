#include "Dungeon.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <QScreen>
#include <QMouseEvent>
#include <QTimer>

#include "resource.h"
#include "gameScene.h"
#include "gameView.h"
#include "collection.h"
#include "level.h"
#include "history.h"
#include "levelParser.h"

Dungeon::Dungeon(QWidget* parent)
    : QMainWindow(parent)
    , hero(new Hero())
    , mDataHandler(std::make_shared<DataHandler>())
    // Initialize the hero
{
    ui.setupUi(this);

    // Initialize the level data
    LevelParser levelParser;
    mLevelData = levelParser.parser(DataResource::kLevel.toStdString());
    currentLevel = mLevelData[0];


    setWindowIcon(QIcon(UIResource::kLogo));

    mMediaPlayer = std::make_shared<MediaPlayer>();
    hero->setPotionSound(mMediaPlayer->potion);
    hero->setMonsterSound(mMediaPlayer->monster);
    hero->setCollectionSound(mMediaPlayer->collection);
    hero->setTrapSound(mMediaPlayer->trap);
    hero->setSuperPotionSound(mMediaPlayer->superPotion);
    hero->setDrangonSound(mMediaPlayer->start);
    hero->setHeroImg(UIResource::kHero);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());

    scene = new GameScene(this);
    scene->setHero(hero);
    scene->setSceneImg(UIResource::kSceneImg);
    scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());

    sceneView = new GameView(scene, this);
    endingScene = new EndingScene(this);
    settingScene = new SettingScene(mMediaPlayer, this);
    introScene = new IntroScene(this);


    settingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    settingScene->setSceneImg(UIResource::kMenu);


    menuScene = new MainMenuScene(this);


    introScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    introScene->setSceneImg(UIResource::kMenu);
    introScene->setMedia(mMediaPlayer);

    menu();
}

void Dungeon::load() {
    mMediaPlayer->mainMenu->stop();
    mMediaPlayer->battle->stop();
    mMediaPlayer->battle->play();

    auto history = mDataHandler->load(DataResource::kData.toStdString());
    currentLevel = mLevelData[history.level - 1];
    scene->loadData(history);
    sceneView->setScene(scene);
    hero->setFocus();
}

void Dungeon::intro() {
    introScene->fadeIn(0);
    sceneView->setScene(introScene);
    introScene->startStory();
    this->setCentralWidget(sceneView);
}

void Dungeon::setting() {
    sceneView->setScene(settingScene);
}

void Dungeon::menu() {
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    menuScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    menuScene->setSceneImg(UIResource::kMenu);

    menuScene->fadeIn(0);
    mMediaPlayer->endingWin->stop();
    mMediaPlayer->endingLose->stop();
    mMediaPlayer->mainMenu->play();
    sceneView->setScene(menuScene);
    this->setCentralWidget(sceneView);
}

void Dungeon::win() {
    mMediaPlayer->battle->stop();
    mMediaPlayer->endingWin->play();
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneImg(UIResource::kWin);
    sceneView->setScene(endingScene);
    endingScene->fadeIn(1000);
    endingScene->setMessage("You Win");
    this->setCentralWidget(sceneView);
}

void Dungeon::lose() {
    mMediaPlayer->battle->stop();
    mMediaPlayer->endingLose->play();
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneImg(UIResource::kLose);
    sceneView->setScene(endingScene);
    endingScene->fadeIn(1000);
    endingScene->setMessage("You Lose");
    this->setCentralWidget(sceneView);
}

void Dungeon::nextLevel() {

    if (std::stoi(currentLevel.level) == mLevelData.size()) {
        std::cout << "It's the highest level, can't move to the next level" << std::endl;
        return;
    }

    mMediaPlayer->nextLevel->play();

    int heroLife = hero->getLife();

    // Continue to the next level
    currentLevel = mLevelData[std::stoi(currentLevel.level)];


    // Recreate the game scene for the new level
    battle();
    // Restore the Hero's life and position in the new scene
    hero->setLife(heroLife);

    hero->setFocus();
    this->setCentralWidget(sceneView);
}

void Dungeon::battle() {
    introScene->fadeOut(4000);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());

    scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    scene->setSceneImg(UIResource::kSceneImg);
    hero->setHeroImg(UIResource::kHero);

    scene->generatorRandomMap(UIResource::kBrickImg, currentLevel);

    QTimer::singleShot(4000, [&]() {sceneView->setScene(scene);  hero->setFocus();
    mMediaPlayer->battle->play();  });
}

void Dungeon::restart() {
    currentLevel = mLevelData[0];
    hero->setLife(3);
    menu();
}
