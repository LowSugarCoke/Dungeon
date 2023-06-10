#include "endingScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QBrush>
#include <QFont>

EndingScene::EndingScene(QObject* parent)
    : QGraphicsScene(parent)
{
    m_backgroundItem = new QGraphicsPixmapItem();
    addItem(m_backgroundItem);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_backgroundItem->setGraphicsEffect(m_opacityEffect);

    m_textItem = new QGraphicsTextItem();
    QFont font;
    font.setPixelSize(300);  // 設置字體大小
    m_textItem->setFont(font);
    m_textItem->setDefaultTextColor(QColor(255, 255, 255));
    addItem(m_textItem);
}

void EndingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    m_backgroundItem->setPixmap(backgroundImage);
}

void EndingScene::setMessage(const QString& message) {
    m_textItem->setPlainText(message);
    m_textItem->setPos((sceneRect().width() - m_textItem->boundingRect().width()) / 2,
        (sceneRect().height() - m_textItem->boundingRect().height()) / 2);  // 將文字置中
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
