/**
 * @file monster.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This header file contains the Monster class, representing a monster in the game.
 */
#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>

class Monster : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT // This macro is needed for any object that uses Qt's signal-slot system

public:
    /**
     * @brief Constructor. It initializes the Monster object.
     */
    Monster();

    /**
     * @brief Sets the image of the monster.
     * @param kMonsterImg A constant reference to a QString object that contains the image file's path.
     */
    void setMonsterImg(const QString& kMonsterImg);

    /**
     * @brief Handles the key press event.
     * @param event A pointer to the QKeyEvent object that describes the event.
     */
    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief Sets the step size of the monster.
     * @param kStepSize A constant reference to an integer specifying the step size.
     */
    void setStepSize(const int& kStepSize);

    /**
     * @brief Makes the monster move randomly.
     */
    void randomMove();

private:
    int mBrickSize;  // Size of the bricks or tiles that make up the game's maze
};
