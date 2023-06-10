#include "hero.h"

#include "monster.h"
#include "gameScene.h"

#include <QPainter>
#include <QKeyEvent>

Hero::Hero()
    : QGraphicsPixmapItem() {
    setFlag(QGraphicsItem::ItemIsFocusable, true);  // Set item to be focusable
  // Update the life text

}


void Hero::setHeroImg(const QString& kHeroImg) {
    QPixmap pixmap(kHeroImg);  // Change this to your image path
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
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
    checkCollision();

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


void Hero::decreaseLife() {
    if (life > 0) {
        --life;
        QPointF newPos(startPos.first, startPos.second);
        setPos(newPos);
    }

    // Update the life text
    GameScene* gameScene = dynamic_cast<GameScene*>(scene());
    if (gameScene) {
        gameScene->updateLifeText(life);
    }

    // if life becomes 0, restart the game or handle game over
    if (life == 0) {
        // handle game over or restart
    }
}

int Hero::getLife() const {
    return life;
}

void Hero::checkCollision() {
    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    for (auto* item : collidingItems) {
        // Check if the colliding item is a monster
        auto* monster = dynamic_cast<Monster*>(item);
        if (monster) {
            this->decreaseLife();
            // ... reset the game or position of hero and monsters
        }
    }
}

void Hero::setStartPos(std::pair<int, int> startPos) {
    this->startPos = startPos;
}
