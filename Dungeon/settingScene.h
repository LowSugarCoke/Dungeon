#pragma once

#include <QGraphicsScene>
#include <QSlider>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include "mediaPlayer.h"

class SettingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    SettingScene(MediaPlayer* player, QObject* parent = nullptr);

    void setSceneImg(const QString& kSceneImg);

    void SettingScene::handleBackButton();

private slots:
    void adjustVolume(int volume);

private:
    QGraphicsPixmapItem* m_backgroundItem;
    MediaPlayer* mediaPlayer;  // 新增的音樂播放器
    QSlider* volumeSlider;  // 新增的音量滑块
    QPushButton* backButton;
};
