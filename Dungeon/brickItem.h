/**
 * @file brickItem.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the BrickItem class, which represents a brick in the game.
 */

#pragma once

 // Includes the QGraphicsPixmapItem class from the Qt library.
#include <QGraphicsPixmapItem>

// The BrickItem class which is a subclass of QGraphicsPixmapItem.
class BrickItem : public QGraphicsPixmapItem
{
public:
    /**
     * @brief Constructor for the BrickItem class.
     *
     * @param parent QGraphicsItem pointer to the parent item. Default value is 0, indicating no parent.
     */
    BrickItem(QGraphicsItem* parent = 0);

    /**
     * @brief Sets the pixmap (image) of the BrickItem object.
     *
     * @param pixmap Reference to the QPixmap object to be set as the pixmap of the BrickItem object.
     */
    void setPixmap(const QPixmap& pixmap);

    /**
     * @brief Provides the bounding rectangle of the BrickItem object.
     *
     * @return QRectF The bounding rectangle of the BrickItem object.
     */
    QRectF boundingRect() const override;
};
