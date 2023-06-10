#include "hero.h"

#include <QPainter>
#include <QKeyEvent>

Hero::Hero()
    : QGraphicsPixmapItem() {
    setFlag(QGraphicsItem::ItemIsFocusable, true);  // Set item to be focusable


}

void Hero::setHeroImg(const QString& kHeroImg) {
    QPixmap pixmap(kHeroImg);  // Change this to your image path
    setPixmap(pixmap.scaled(QSize(35, 35), Qt::KeepAspectRatio));
}

void Hero::keyPressEvent(QKeyEvent* event) {
    // Calculate new position
    QPointF newPos = pos();
    QPointF beforePos = pos();
    if (event->key() == Qt::Key_W) {
        newPos.setY(newPos.y() - brickSize);
    }
    else if (event->key() == Qt::Key_S) {
        newPos.setY(newPos.y() + brickSize);
    }
    else if (event->key() == Qt::Key_A) {
        newPos.setX(newPos.x() - brickSize);
    }
    else if (event->key() == Qt::Key_D) {
        newPos.setX(newPos.x() + brickSize);
    }

    // Check for collisions
    setPos(newPos);
    if (!collidingItems().isEmpty()) {
        // If colliding with any item, undo move
        setPos(beforePos);
        return;
    }

    QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}

void Hero::setStepSize(const int& kStepSize) {
    brickSize = kStepSize;
}
