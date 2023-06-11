#pragma once

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
    IntroScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);
    void setMedia(MediaPlayer* player);
    void startStory();


private:
    void handleStartButton();
    MediaPlayer* mediaPlayer;  // 新增的音樂播放器


    QGraphicsPixmapItem* m_backgroundItem;
    QGraphicsOpacityEffect* m_opacityEffect;

    QGraphicsTextItem* m_textItem;
    QPushButton* startButton;

    QString m_story;
    int m_storyIndex;
    QTimer* m_storyTimer;
    QGraphicsPixmapItem* m_title;


private slots:
    void updateStory();
};
