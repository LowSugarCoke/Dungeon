#pragma once

#include <QGraphicsScene>
#include <QSlider>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPushButton>
#include "mediaPlayer.h"

class MainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainMenuScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);
    void setMedia(MediaPlayer* player);


private:
    QGraphicsPixmapItem* m_backgroundItem;
    QGraphicsOpacityEffect* m_opacityEffect;
    MediaPlayer* mediaPlayer;  // 新增的音樂播放器

    QPushButton* startButton;
    QPushButton* settingsButton;
    QPushButton* exitButton;
    QGraphicsPixmapItem* m_title;

private slots:
    void handleStartButton();
    void handleSettingsButton();
    void handleExitButton();



};
