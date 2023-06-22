/**
 * @file trap.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the Trap class, which represents a trap in the game.
 */

#pragma once

#include <QGraphicsPixmapItem>

class BrickItem : public QGraphicsPixmapItem
{
public:
    BrickItem(QGraphicsItem* parent = 0);
    void setPixmap(const QPixmap& pixmap);
    QRectF boundingRect() const override;
};
