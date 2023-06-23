#include "gameView.h"

#include <QPoint>
#include <QResizeEvent>

#include "gameScene.h"

GameView::GameView(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {

}

void GameView::resizeEvent(QResizeEvent* event) {
    if (scene())
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
    QGraphicsView::resizeEvent(event);
}


void GameView::mousePressEvent(QMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->pos());
    if (!item || dynamic_cast<QGraphicsPixmapItem*>(item)) {
        // Ignore mouse press on QGraphicsPixmapItem
        return;
    }
    QGraphicsView::mousePressEvent(event);
}
