#include "monster.h"

#include "hero.h"

#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QCoreApplication>

Monster::Monster()
    : QGraphicsPixmapItem() {
    setFlag(QGraphicsItem::ItemIsFocusable, true);  // Set item to be focusable


}



void Monster::setMonsterImg(const QString& kMonsterImg) {
    QPixmap pixmap(kMonsterImg);  // Change this to your image path
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Monster::keyPressEvent(QKeyEvent* event) {
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


        // Check for collisions with the hero after the move
        QList<QGraphicsItem*> collidingItems = this->collidingItems();

        for (auto* item : collidingItems) {
            // Check if the colliding item is the hero
            auto* hero = dynamic_cast<Hero*>(item);
            if (hero) {
                hero->checkCollision();
            }
        }

        // If colliding with any item, undo move
        setPos(beforePos);
        return;
    }



    QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}

void Monster::setStepSize(const int& kStepSize) {
    brickSize = kStepSize;
}


void Monster::randomMove() {
    // Choose a random direction for the monster to move in
    int direction = QRandomGenerator::global()->bounded(4);
    QKeyEvent* event;
    switch (direction) {
    case 0:
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
        break;
    case 1:
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
        break;
    case 2:
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
        break;
    case 3:
        event = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
        break;
    default:
        return;
    }

    // Pass the event to keyPressEvent function
    keyPressEvent(event);
    delete event;  // Don't forget to delete the event after we are done

}