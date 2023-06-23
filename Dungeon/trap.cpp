#include "trap.h"

#include <QPixmap>

Trap::Trap()
    : QGraphicsPixmapItem() {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
}

void Trap::setImg(const QString& kTrapImg) {
    QPixmap pixmap(kTrapImg);
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}
