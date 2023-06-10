#include "Dungeon.h"

#include <QScreen>

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
    auto sceneView = new GameView(scene, this);

    this->setCentralWidget(sceneView);
}
