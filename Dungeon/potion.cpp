#include "potion.h"

#include <QPixmap>

Potion::Potion()
    : QGraphicsPixmapItem() {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
}

void Potion::setImg(const QString& kPotionImg) {
    QPixmap pixmap(kPotionImg);
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Potion::disappear() {
    this->hide();
}
