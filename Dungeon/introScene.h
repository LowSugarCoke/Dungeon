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
    IntroScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);
    void setMedia(std::shared_ptr<MediaPlayer> mediaPlayer);
    void startStory();


private:
    void handleStartButton();
    std::shared_ptr<MediaPlayer> mMediaPlayer;

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
