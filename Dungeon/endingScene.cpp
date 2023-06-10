#include "endingScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QBrush>

EndingScene::EndingScene(QObject* parent)
    : QGraphicsScene(parent)
{
    m_backgroundItem = new QGraphicsPixmapItem();
    addItem(m_backgroundItem);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_backgroundItem->setGraphicsEffect(m_opacityEffect);
}

void EndingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    m_backgroundItem->setPixmap(backgroundImage);
}


void EndingScene::fadeIn(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void EndingScene::fadeOut(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
