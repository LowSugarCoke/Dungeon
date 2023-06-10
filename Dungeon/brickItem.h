#pragma once

#include <QGraphicsPixmapItem>

class BrickItem : public QGraphicsPixmapItem
{
public:
    BrickItem(QGraphicsItem* parent = 0);
    void setPixmap(const QPixmap& pixmap);
};
