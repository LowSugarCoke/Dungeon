/**
 * @file settingScene.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This header file contains the SettingScene class, which manages the setting scene of the game.
 */

#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QSlider>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include "mediaPlayer.h"

class SettingScene : public QGraphicsScene
{
    Q_OBJECT // This macro is needed for any object that uses Qt's signal-slot system
public:
    /**
     * @brief Constructor. It initializes the SettingScene with a MediaPlayer object.
     * @param mediaPlayer A shared pointer to a MediaPlayer object which manages all the media in the game.
     * @param parent The parent object in Qt's parent-child system.
     */
    SettingScene(std::shared_ptr<MediaPlayer> mediaPlayer, QObject* parent = nullptr);

    /**
     * @brief Sets the background image of the setting scene.
     * @param kSceneImg A constant reference to a QString object that contains the image file's path.
     */
    void setSceneImg(const QString& kSceneImg);

private slots:
    /**
     * @brief Slot that adjusts the volume of the game's sound effects.
     * @param volume An integer that specifies the volume level.
     */
    void adjustVolume(int volume);

    /**
     * @brief Slot that handles the action when the back button is clicked.
     */
    void handleBackButton();

private:
    std::shared_ptr<MediaPlayer> mMediaPlayer;  // Media player
    std::shared_ptr<QSlider> mVolumeSlider;                    // Slider for adjusting the volume
    std::shared_ptr<QPushButton> mBackButton;                  // Button for going back to the previous scene
    std::shared_ptr<QGraphicsTextItem> mTextItem;              // Text item for displaying the volume level
};
