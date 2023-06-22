/**
 * @file endingScene.h
 * @author Jack Lee
 * @date 2023.06.23
 *
 * @brief The file contains the EndingScene class which defines the final scene of the game, typically displayed at the end of the game. It displays the final message and provides a restart button.
 */

#pragma once

 // Include relevant Qt classes
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPushButton>

// The EndingScene class represents the final scene of the game.
class EndingScene : public QGraphicsScene
{
    Q_OBJECT  // This macro is required for any object that uses Qt's signal-slot system
public:

    /**
     * @brief Constructor for the EndingScene class.
     * @param parent An optional parent QObject. Default is nullptr.
     */
    EndingScene(QObject* parent = nullptr);

    /**
     * @brief Set the background image for the scene.
     * @param kSceneImg The path of the image file.
     */
    void setSceneImg(const QString& kSceneImg);

    /**
     * @brief Perform a fade-in animation over a specified duration.
     * @param duration The duration of the fade-in animation in milliseconds.
     */
    void fadeIn(int duration);

    /**
     * @brief Perform a fade-out animation over a specified duration.
     * @param duration The duration of the fade-out animation in milliseconds.
     */
    void fadeOut(int duration);

    /**
     * @brief Set the final message to be displayed in the scene.
     * @param message The final message text.
     */
    void setMessage(const QString& message);

private:
    /**
     * @brief Handle the action when the restart button is clicked.
     */
    void handleRestartButton();

private:
    // Private member variables
    QGraphicsPixmapItem* mBackgroundItem;  // The background item
    QGraphicsOpacityEffect* mOpacityEffect;  // The opacity effect for fade-in and fade-out animations
    QGraphicsTextItem* mTextItem;  // The text item for the final message
    QPushButton* mBackButton;  // The restart button
};
