#include "potion.h"

#include <QPixmap>

Potion::Potion()
    : QGraphicsPixmapItem() {}

void Potion::setPotionImg(const QString& kPotionImg) {
    QPixmap pixmap(kPotionImg);
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Potion::disappear() {
    this->hide();
}
