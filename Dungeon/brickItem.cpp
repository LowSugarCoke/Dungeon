#include "brickItem.h"

BrickItem::BrickItem(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent) {}

void BrickItem::setPixmap(const QPixmap& kPixmap)
{
    QGraphicsPixmapItem::setPixmap(kPixmap);
}

QRectF BrickItem::boundingRect() const {
    return pixmap().rect();
}
