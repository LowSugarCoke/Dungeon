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
    mBackgroundItem = new QGraphicsPixmapItem();
    addItem(mBackgroundItem);
    mOpacityEffect = new QGraphicsOpacityEffect();
    mBackgroundItem->setGraphicsEffect(mOpacityEffect);

    mTextItem = new QGraphicsTextItem();
    QFont font;
    font.setPixelSize(300);
    mTextItem->setFont(font);
    mTextItem->setDefaultTextColor(QColor(255, 255, 255));
    addItem(mTextItem);

    mBackButton = new QPushButton(QString::fromLocal8Bit("重新遊戲"));
    mBackButton->setMinimumSize(400, 120);
    mBackButton->setMaximumSize(400, 120);
    mBackButton->setStyleSheet(R"(
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
    QGraphicsProxyWidget* backButtonProxy = addWidget(mBackButton);
    backButtonProxy->setPos(750, 700);  // 调整位置
    connect(mBackButton, &QPushButton::clicked, this, &EndingScene::handleRestartButton);
}

void EndingScene::handleRestartButton() {
    static_cast<Dungeon*>(parent())->restart();

}

void EndingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    mBackgroundItem->setPixmap(backgroundImage);
}

void EndingScene::setMessage(const QString& message) {
    mTextItem->setPlainText(message);
    mTextItem->setPos((sceneRect().width() - mTextItem->boundingRect().width()) / 2, (150));
}

void EndingScene::fadeIn(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(mOpacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void EndingScene::fadeOut(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(mOpacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
