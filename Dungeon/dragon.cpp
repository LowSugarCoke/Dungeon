#include "dragon.h"

#include "collection.h"
#include "potion.h"
#include "trap.h"
#include "brickItem.h"
#include "superPotion.h"

#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QCoreApplication>

#include "resource.h"

// Constructor for the Dragon class
Dragon::Dragon(Hero* mHero)
    : QGraphicsPixmapItem(),  // Initialize the QGraphicsPixmapItem base class
    mHero(mHero),  // Initialize mHero with the provided Hero pointer
    mSpeedMultiplier(1.0f) {  // Initialize the speed multiplier
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
    mBoundary = QRectF(140, 70, 1400, 700);  // Set the boundary within which the dragon can move
    QPixmap pixmap(UIResource::kExclamationMark);  // Load the pixmap for the exclamation mark
    mExclamationMark = new QGraphicsPixmapItem(pixmap.scaled(QSize(50, 50), Qt::KeepAspectRatio), this);  // Initialize the exclamation mark item
    mExclamationMark->setPos(pos().x() + 110, pos().y() - mExclamationMark->boundingRect().height());  // Position the exclamation mark
    mExclamationMark->setVisible(false);  // Make the exclamation mark invisible by default
}

// Method to set the image of the dragon
void Dragon::setDragonImg(const QString& kDragonImg) {
    QPixmap pixmap(kDragonImg);  // Load the pixmap from the provided path
    setPixmap(pixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio));  // Set the pixmap of the dragon item
}

// Method to handle key press events
void Dragon::keyPressEvent(QKeyEvent* event) {
    // Calculate new position based on the pressed key and the current position
    // Check if the new position is within the boundary and if there are any collisions
    // If the new position is valid, move the dragon to the new position

    QPointF newPos = pos();
    QPointF beforePos = pos();
    if (event->key() == Qt::Key_W) {
        newPos.setY(newPos.y() - mBrickSize * mSpeedMultiplier);
    }
    else if (event->key() == Qt::Key_S) {
        newPos.setY(newPos.y() + mBrickSize * mSpeedMultiplier);
    }
    else if (event->key() == Qt::Key_A) {
        newPos.setX(newPos.x() - mBrickSize * mSpeedMultiplier);
    }
    else if (event->key() == Qt::Key_D) {
        newPos.setX(newPos.x() + mBrickSize * mSpeedMultiplier);
    }

    // Check if the new position is within the mBoundary
    if (!mBoundary.contains(newPos)) {
        return;  // If the new position is out of mBoundary, do not move
    }

    // Check for collisions
    setPos(newPos);

    if (!collidingItems().isEmpty()) {
        // Check for collisions with the mHero after the move
        QList<QGraphicsItem*> collidingItems = this->collidingItems();

        for (auto* item : collidingItems) {
            // Check if the colliding item is the mHero
            auto* mHero = dynamic_cast<Hero*>(item);
            if (mHero) {
                mHero->checkCollision();
                // If colliding with any item, undo move
            }
        }
    }

    QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}


// Method to set the step size for the dragon
void Dragon::setStepSize(const int& kStepSize) {
    mBrickSize = kStepSize;
}

// Method to move the dragon randomly
void Dragon::randomMove() {
    // Check if the hero is in the detection range
    // If the hero is detected, move towards the hero
    // If the hero is not detected, move in a random direction

    qreal distanceToHero = QLineF(pos(), mHero->pos()).length();
    if (distanceToHero < 300) {
        mExclamationMark->setVisible(true);

        if (pos().x() < mHero->pos().x()) {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
        else {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }

        if (pos().y() < mHero->pos().y()) {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
        else {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
    }
    else {
        mExclamationMark->setVisible(false);
        QKeyEvent* event;

        if (QRandomGenerator::global()->bounded(2) == 0) {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
        else {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }

        if (QRandomGenerator::global()->bounded(2) == 0) {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
        else {
            QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
            keyPressEvent(event);
            delete event;
        }
    }
}
