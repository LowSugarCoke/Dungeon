/**
 * @file dragon.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file contains the Dragon class, which represents a dragon character in the game.
 */

#pragma once

 // Include necessary Qt classes and the Hero class
#include <QObject>
#include <QGraphicsPixmapItem>
#include "hero.h"

// The Dragon class represents a dragon character in the game. It inherits from QObject and QGraphicsPixmapItem.
class Dragon : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT // This macro is necessary for any object that uses the Qt's signals and slots mechanism

public:

    /**
     * @brief Constructor for the Dragon class.
     *
     * @param mHero A pointer to a Hero object representing the hero character in the game.
     */
    Dragon(Hero* mHero);

    // Virtual destructor for the Dragon class
    virtual ~Dragon() {}

    /**
     * @brief Sets the image of the Dragon object.
     *
     * @param kDragonImg A QString representing the file path to the image for the Dragon object.
     */
    void setDragonImg(const QString& kDragonImg);

    /**
     * @brief Handles key press events for the Dragon object.
     *
     * @param event A pointer to a QKeyEvent object representing the key press event.
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief Sets the step size for the Dragon object, affecting how much it moves in response to a key press event.
     *
     * @param kStepSize An integer representing the step size.
     */
    void setStepSize(const int& kStepSize);

    /**
     * @brief Makes the Dragon object move randomly.
     */
    void randomMove();

private:
    // Size of the bricks in the game, used to determine the boundaries of movement for the Dragon object
    int mBrickSize;

    // A pointer to a Hero object representing the hero character in the game
    Hero* mHero;

    // Multiplier to adjust the speed of the Dragon object
    float mSpeedMultiplier;

    // The boundaries within which the Dragon object can move
    QRectF mBoundary;

    // A pointer to a QGraphicsPixmapItem object representing an exclamation mark, typically displayed when the Dragon object notices the Hero object
    QGraphicsPixmapItem* mExclamationMark;
};
