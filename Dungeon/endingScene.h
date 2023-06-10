#pragma once

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>

class EndingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    EndingScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);
    void setMessage(const QString& message);

private:
    QGraphicsPixmapItem* m_backgroundItem;
    QGraphicsOpacityEffect* m_opacityEffect;

    QGraphicsTextItem* m_textItem;
};
