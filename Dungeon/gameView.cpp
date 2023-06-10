#include "gameView.h"

#include <QPoint>
#include <QResizeEvent>

#include "gameScene.h"

GameView::GameView(GameScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent)
{
}

void GameView::resizeEvent(QResizeEvent* event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
}
