/**
 * @file trap.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the Trap class, which represents a trap in the game.
 */

#pragma once

#include <QGraphicsPixmapItem>

class Trap : public QGraphicsPixmapItem {
public:

    /**
     * @brief Constructor for the Trap class.
     *
     * This constructor creates a new Trap object. The trap is initially invisible and can be placed anywhere on the
     * game map. The image used to represent the trap can be set using the setTrapImg method.
     */
    Trap();

    /**
     * @brief Sets the image used to represent the trap.
     *
     * This method sets the QPixmap that is used to represent the trap in the game. The QPixmap is loaded from a
     * file specified by the QString parameter. If the file cannot be found or loaded, the trap will be represented
     * by a default image.
     *
     * @param kTrapImg The path to the image file to use to represent the trap.
     */
    void setImg(const QString& kTrapImg);
};
