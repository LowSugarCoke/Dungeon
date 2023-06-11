#include "Dungeon.h"

#include <QScreen>
#include <QMouseEvent>
#include <QTimer>

#include "resource.h"
#include "gameScene.h"
#include "gameView.h"
#include "collection.h"
#include "level.h"

Dungeon::Dungeon(QWidget* parent)
    : QMainWindow(parent)
    , currentLevel(Level::kEasy)
    , hero(new Hero())
    // Initialize the hero
{
    ui.setupUi(this);

    mediaPlayer = new MediaPlayer();
    hero->setPotionSound(mediaPlayer->potion);
    hero->setMonsterSound(mediaPlayer->monster);
    hero->setCollectionSound(mediaPlayer->collection);
    hero->setTrapSound(mediaPlayer->trap);
    mediaPlayer->mainMenu->play();

    scene = new GameScene(this);


    sceneView = new GameView(scene, this);
    endingScene = new EndingScene(this);
    settingScene = new SettingScene(mediaPlayer, this);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    settingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    settingScene->setSceneImg(UIResource::kMenu);

    menuScene = new MainMenuScene(this);
    menuScene->setMedia(mediaPlayer);

    menu();

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
    mediaPlayer->endingWin->stop();
    mediaPlayer->endingLose->stop();
    mediaPlayer->mainMenu->play();
    sceneView->setScene(menuScene);
    this->setCentralWidget(sceneView);
}

void Dungeon::win() {
    mediaPlayer->battle->stop();
    mediaPlayer->endingWin->play();
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
    mediaPlayer->battle->stop();
    mediaPlayer->endingLose->play();
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
    int heroLife = hero->getLife();

    // Continue to the next level
    if (currentLevel.level == Level::kEasy.level) {
        currentLevel = Level::kMedium;
    }
    else if (currentLevel.level == Level::kMedium.level) {
        currentLevel = Level::kHard;
    }

    // Recreate the game scene for the new level
    battle();
    // Restore the Hero's life and position in the new scene
    hero->setLife(heroLife);

    hero->setFocus();
    this->setCentralWidget(sceneView);

}

void Dungeon::battle() {

    menuScene->fadeOut(4000);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());

    scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    scene->setSceneImg(UIResource::kSceneImg);
    hero->setHeroImg(UIResource::kHero);
    scene->setHero(hero);

    scene->generatorRandomMap(UIResource::kBrickImg, currentLevel);

    QTimer::singleShot(4000, [&]() {sceneView->setScene(scene);  hero->setFocus();
    mediaPlayer->battle->play(); });

    //this->showFullScreen();
}

void Dungeon::restart() {
    currentLevel = Level::kEasy;
    hero->setLife(3);
    menu();
}
