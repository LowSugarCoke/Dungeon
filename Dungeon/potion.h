/**
 * @file potion.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the Potion class, which represents a potion in the game.
 */

#pragma once
#include <QGraphicsPixmapItem>

class Potion : public QGraphicsPixmapItem {
public:
    /**
     * @brief Constructor for the Potion class.
     *
     * This constructor creates a new Potion object. The potion is initially invisible and can be placed anywhere on the
     * game map. The image used to represent the potion can be set using the setPotionImg method.
     */
    Potion();

    /**
     * @brief Sets the image used to represent the potion.
     *
     * This method sets the QPixmap that is used to represent the potion in the game. The QPixmap is loaded from a
     * file specified by the QString parameter. If the file cannot be found or loaded, the potion will be represented
     * by a default image.
     *
     * @param kPotionImg The path to the image file to use to represent the potion.
     */
    void setPotionImg(const QString& kPotionImg);

    /**
     * @brief Makes the potion disappear from the game map.
     *
     * This method is used when the player collects the potion. The potion will disappear from the map, and it
     * will also be removed from any data structures that track the locations of items on the map.
     */
    void disappear();

};
