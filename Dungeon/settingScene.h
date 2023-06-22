#pragma once

#include <memory>

#include <QGraphicsScene>
#include <QSlider>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include "mediaPlayer.h"

class SettingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SettingScene(std::shared_ptr<MediaPlayer> mediaPlayer, QObject* parent = nullptr);

    void setSceneImg(const QString& kSceneImg);



private slots:
    void adjustVolume(int volume);
    void handleBackButton();

private:
    QGraphicsPixmapItem* m_backgroundItem;
    std::shared_ptr<MediaPlayer> mMediaPlayer;
    QSlider* volumeSlider;
    QPushButton* backButton;

    QGraphicsTextItem* m_textItem;
};
