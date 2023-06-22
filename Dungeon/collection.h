/**
 * @file collection.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief The file contains the Collection class, representing a collectible item in a game.
 */

#pragma once

 // Includes the QGraphicsPixmapItem class from the Qt library.
#include <QGraphicsPixmapItem>

// The Collection class is a subclass of QGraphicsPixmapItem and represents a collectible item in the game.
class Collection : public QGraphicsPixmapItem {

public:

    /**
     * @brief Constructor for the Collection class.
     *
     * Initializes a new instance of the Collection class.
     */
    Collection();

    /**
     * @brief Sets the image of the Collection object.
     *
     * @param kCollectionImg A QString representing the file path to the image for the Collection object.
     */
    void setCollectionImg(const QString& kCollectionImg);

    /**
     * @brief Makes the Collection object disappear, typically after it has been collected in the game.
     */
    void disappear();

};
