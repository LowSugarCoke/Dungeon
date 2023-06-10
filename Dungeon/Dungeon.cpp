#include "Dungeon.h"

#include <QScreen>

#include "resource.h"
#include "gameScene.h"
#include "gameView.h"

Dungeon::Dungeon(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    initUI();
}

void Dungeon::initUI() {

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());

    GameScene* scene = new GameScene(this);
    scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    scene->setSceneImg(UIResource::kSceneImg);
    scene->generatorRandomMap(UIResource::kBrickImg, Level::kMedium);

    auto sceneView = new GameView(scene, this);

    this->setCentralWidget(sceneView);
    //this->showFullScreen();
}
