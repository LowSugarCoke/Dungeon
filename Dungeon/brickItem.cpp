#include "brickItem.h"

BrickItem::BrickItem(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{

}

void BrickItem::setPixmap(const QPixmap& kPixmap)
{
    QGraphicsPixmapItem::setPixmap(kPixmap);
}

QRectF BrickItem::boundingRect() const {
    // Use the pixmap's rectangle as the bounding rectangle
    return pixmap().rect();
}
