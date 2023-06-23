// collection.cpp
#include "collection.h"
#include "gameScene.h"

#include <QPixmap>

Collection::Collection()
    : QGraphicsPixmapItem() {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
}

void Collection::setImg(const QString& kCollectionImg) {
    QPixmap pixmap(kCollectionImg);
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Collection::disappear() {
    QGraphicsPixmapItem::hide();

    GameScene* gameScene = dynamic_cast<GameScene*>(scene());
    gameScene->decreaseCollectionCount();

    if (gameScene->isAllCollectionsCollected()) {
        gameScene->nextLevel();
    }
}
