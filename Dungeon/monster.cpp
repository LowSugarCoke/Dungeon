#include "monster.h"

#include "hero.h"
#include "collection.h"
#include "potion.h"
#include "trap.h"
#include "superPotion.h"

#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QCoreApplication>

Monster::Monster()
    : QGraphicsPixmapItem() {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
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
        newPos.setY(newPos.y() - mBrickSize);
    }
    else if (event->key() == Qt::Key_S) {
        newPos.setY(newPos.y() + mBrickSize);
    }
    else if (event->key() == Qt::Key_A) {
        newPos.setX(newPos.x() - mBrickSize);
    }
    else if (event->key() == Qt::Key_D) {
        newPos.setX(newPos.x() + mBrickSize);
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
                // If colliding with any item, undo move
            }

            auto* collection = dynamic_cast<Collection*>(item);
            auto* potion = dynamic_cast<Potion*>(item);
            auto* trap = dynamic_cast<Trap*>(item);
            auto* superPotion = dynamic_cast<SuperPotion*>(item);

            if (!(collection || potion || trap || superPotion)) {
                setPos(beforePos);
                return;
            }
        }
    }

    QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}

void Monster::setStepSize(const int& kStepSize) {
    mBrickSize = kStepSize;
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
