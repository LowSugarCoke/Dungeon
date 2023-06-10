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

    scene = new GameScene(this);
    sceneView = new GameView(scene, this);
    endingScene = new EndingScene(this);




    initUI();
}

void Dungeon::win() {
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    endingScene->setSceneImg(UIResource::kWin);
    sceneView->setScene(endingScene);
    endingScene->fadeIn(1000);
    this->setCentralWidget(sceneView);
}

void Dungeon::nextLevel() {
    int heroLife = hero->getLife();
    QPointF heroPos = hero->pos();

    // Continue to the next level
    if (currentLevel.level == Level::kEasy.level) {
        currentLevel = Level::kMedium;
    }
    else if (currentLevel.level == Level::kMedium.level) {
        currentLevel = Level::kHard;
    }

    // Recreate the game scene for the new level
    initUI();
    // Restore the Hero's life and position in the new scene
    hero->setLife(heroLife);
    hero->setPos(heroPos);
    hero->setFocus();
    this->setCentralWidget(sceneView);

}

void Dungeon::initUI() {

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());





    scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    scene->setSceneImg(UIResource::kSceneImg);

    hero->setHeroImg(UIResource::kHero);
    scene->setHero(hero);

    scene->generatorRandomMap(UIResource::kBrickImg, currentLevel);



    this->setCentralWidget(sceneView);
    hero->setFocus();
    //this->showFullScreen();
}
