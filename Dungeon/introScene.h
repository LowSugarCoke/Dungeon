/**
 * @file introScene.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file declares the IntroScene class which represents the introduction scene of the game.
 */

#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include <QTimer>

#include "mediaPlayer.h"

class IntroScene : public QGraphicsScene
{
    Q_OBJECT
public:

    /**
     * @brief Constructor for the IntroScene class.
     * @param parent The parent QObject that owns this IntroScene.
     */
    IntroScene(QObject* parent = nullptr);

    /**
     * @brief Set the image of the scene.
     * @param kSceneImg The image to set.
     */
    void setSceneImg(const QString& kSceneImg);

    /**
     * @brief Create a fade in animation over the specified duration.
     * @param duration The duration of the animation in milliseconds.
     */
    void fadeIn(int duration);

    /**
     * @brief Create a fade out animation over the specified duration.
     * @param duration The duration of the animation in milliseconds.
     */
    void fadeOut(int duration);

    /**
     * @brief Set the MediaPlayer for the scene.
     * @param mediaPlayer The MediaPlayer to set.
     */
    void setMedia(std::shared_ptr<MediaPlayer> mediaPlayer);

    /**
     * @brief Begin displaying the story.
     */
    void startStory();


private:

    /**
     * @brief Handle the event when the start button is clicked.
     */
    void handleStartButton();

    std::shared_ptr<MediaPlayer> mMediaPlayer;  // The MediaPlayer for the scene.
    QGraphicsPixmapItem* mBackgroundItem;  // The background image of the scene.
    QGraphicsOpacityEffect* mOpacityEffect;  // The opacity effect used for fade in/out.

    QGraphicsTextItem* mTextItem;  // The text item used to display the story.
    QPushButton* mStartButton;  // The start button.

    QTimer* mStoryTimer;  // The timer used for displaying the story.
    QGraphicsPixmapItem* mTitle;  // The title of the scene.

    QString mStory;  // The story text.
    int mStoryIndex;  // The index of the current position in the story.

private slots:

    /**
     * @brief Update the display of the story.
     */
    void updateStory();
};
