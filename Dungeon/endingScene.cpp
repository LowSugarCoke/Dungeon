#include "endingScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsProxyWidget>
#include <QBrush>
#include <QFont>

#include "Dungeon.h"

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

    backButton = new QPushButton(QString::fromLocal8Bit("重新遊戲"));
    backButton->setMinimumSize(400, 120);
    backButton->setMaximumSize(400, 120);
    backButton->setStyleSheet(R"(
    QPushButton { 
        font-size:20px; 
        font-weight:bold; 
        background:none; 
        background-color:transparent; 
        border-image: url(Resources/img/button.png) 0 0 0 0 stretch stretch; 
    }
    QPushButton:hover { 
        color:white;
    }
    QPushButton:pressed { 
        color:black;
    }
)");
    QGraphicsProxyWidget* backButtonProxy = addWidget(backButton);
    backButtonProxy->setPos(750, 700);  // 调整位置
    connect(backButton, &QPushButton::clicked, this, &EndingScene::handleRestartButton);
}

void EndingScene::handleRestartButton() {
    static_cast<Dungeon*>(parent())->restart();

}

void EndingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    m_backgroundItem->setPixmap(backgroundImage);
}

void EndingScene::setMessage(const QString& message) {
    m_textItem->setPlainText(message);
    m_textItem->setPos((sceneRect().width() - m_textItem->boundingRect().width()) / 2,
        (150));  // 將文字置中
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
