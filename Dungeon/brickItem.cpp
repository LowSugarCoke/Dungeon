#include "brickItem.h"

BrickItem::BrickItem(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) {
    this->setFlag(QGraphicsItem::ItemIsFocusable, false);
}

void BrickItem::setPixmap(const QPixmap& kPixmap)
{
    QGraphicsPixmapItem::setPixmap(kPixmap);
}

QRectF BrickItem::boundingRect() const {
    return pixmap().rect();
}
