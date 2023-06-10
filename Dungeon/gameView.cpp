#include "gameView.h"

#include <string>

#include <QPoint>
#include <QResizeEvent>

const static QString kDefaultSceneImg = "Resources\\img\\scene.jpg";

GameScene::GameScene(QObject* parent)
    : QGraphicsScene(parent) {
    QImage backgroundImage(kDefaultSceneImg);
    setBackgroundBrush(QBrush(backgroundImage));
}

GameView::GameView(GameScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
}

void GameView::resizeEvent(QResizeEvent* event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
}
