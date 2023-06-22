#include "introScene.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsProxyWidget>
#include <QBrush>
#include <QFont>


#include "Dungeon.h"
#include "resource.h"

IntroScene::IntroScene(QObject* parent)
    : QGraphicsScene(parent)
{
    m_story = QString::fromLocal8Bit("在遙遠的過去，曾有一個充滿魔法與神秘的世界，被稱為“艾瑞亞”。\n")
        + QString::fromLocal8Bit("這個世界由龍們統治，他們富有智慧，擁有強大的魔法力量。\n")
        + QString::fromLocal8Bit("但是，在這個和平的世界裡，一個陰影悄然升起，那就是邪惡的法師薩格斯。\n")
        + QString::fromLocal8Bit("他渴望將艾瑞亞所有的力量納入己身。\n")
        + QString::fromLocal8Bit("薩格斯的權力日益強大，他不滿足於僅僅統治艾瑞亞，他還渴望得到更多。\n")
        + QString::fromLocal8Bit("他對所有的龍發動了戰爭，並利用強大的黑暗魔法，將龍們一一打敗，並將他們的力量吸收到自己的身體中。\n")
        + QString::fromLocal8Bit("然而，這些龍們並非無法抵抗。\n")
        + QString::fromLocal8Bit("在被打敗的前夕，他們將自己的力量注入了一個神秘的寶藏之中，並把它藏在了一個只有真正的英雄才能到達的地方。\n")
        + QString::fromLocal8Bit("時間流逝，薩格斯的邪惡統治仍在繼續，然而，人們對和平的渴望並未消失。\n")
        + QString::fromLocal8Bit("他們一直在尋找那個能夠挑戰薩格斯，並將艾瑞亞從他魔爪中解救出來的英雄。\n")
        + QString::fromLocal8Bit("這就是你的角色出場的時候。你將扮演其中的一個勇者，冒著生命危險，踏上了尋找神秘寶藏的旅程。\n")
        + QString::fromLocal8Bit("你將會遇到艱難的挑戰、巧妙的陷阱、強大的怪物，但是，只有你能夠打敗薩格斯，恢復艾瑞亞的和平。");

    m_storyTimer = new QTimer(this);
    connect(m_storyTimer, &QTimer::timeout, this, &IntroScene::updateStory);

    m_storyIndex = 0;
    m_storyTimer = new QTimer(this);
    connect(m_storyTimer, &QTimer::timeout, this, &IntroScene::updateStory);

    m_backgroundItem = new QGraphicsPixmapItem();
    addItem(m_backgroundItem);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_opacityEffect->setOpacity(1.0);
    m_backgroundItem->setGraphicsEffect(m_opacityEffect);

    QGraphicsRectItem* m_backgroundRect = new QGraphicsRectItem();
    addItem(m_backgroundRect);
    QBrush brush(QColor(255, 255, 255));  // 使用白色作為背景色
    m_backgroundRect->setBrush(brush);


    m_textItem = new QGraphicsTextItem();
    QFont font;
    font.setPixelSize(30);  // 設置字體大小
    font.setWeight(QFont::Black); // 将字体设置为最粗

    m_textItem->setFont(font);
    m_textItem->setDefaultTextColor(QColor(150, 200, 200));
    addItem(m_textItem);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_opacityEffect->setOpacity(1.0);
    m_textItem->setGraphicsEffect(m_opacityEffect);
    m_textItem->hide();

    startButton = new QPushButton(QString::fromLocal8Bit("開始遊戲"));
    startButton->hide();
    startButton->setMinimumSize(400, 120);
    startButton->setMaximumSize(400, 120);
    startButton->setStyleSheet(R"(
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
    QGraphicsProxyWidget* startButtonProxy = addWidget(startButton);
    startButtonProxy->setPos(750, 700);  // 调整位置
    connect(startButton, &QPushButton::clicked, this, &IntroScene::handleStartButton);

    m_title = new QGraphicsPixmapItem();
    addItem(m_title);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_opacityEffect->setOpacity(1.0);
    m_title->setGraphicsEffect(m_opacityEffect);

    QPixmap backgroundImage(UIResource::kTitle);
    m_title->setPixmap(backgroundImage);
    m_title->setPos(50, 50);
}


void IntroScene::startStory() {
    m_textItem->show();
    m_storyTimer->start(10);  // every 0.1 second
    m_textItem->setPlainText(m_story);
    m_textItem->setPos(200, 400);


}

void IntroScene::updateStory() {
    m_textItem->setPos(200, m_textItem->pos().y() - 1);
    if (m_textItem->pos().y() <= height() / 4) {
        m_storyTimer->stop();
        startButton->show();
    }
}


void IntroScene::handleStartButton() {
    static_cast<Dungeon*>(parent())->battle();
    mediaPlayer->mainMenu->stop();
    mediaPlayer->start->play();


}

void IntroScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    m_backgroundItem->setPixmap(backgroundImage);
}

void IntroScene::fadeIn(int duration) {

    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // For m_textItem
    QPropertyAnimation* textAnimation = new QPropertyAnimation(m_textItem->graphicsEffect(), "opacity");
    textAnimation->setDuration(duration);
    textAnimation->setStartValue(0.0);
    textAnimation->setEndValue(1.0);
    textAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void IntroScene::fadeOut(int duration) {
    startButton->hide();
    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // For m_textItem
    QPropertyAnimation* textAnimation = new QPropertyAnimation(m_textItem->graphicsEffect(), "opacity");
    textAnimation->setDuration(duration);
    textAnimation->setStartValue(1.0);
    textAnimation->setEndValue(0.0);
    textAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void IntroScene::setMedia(MediaPlayer* player) {
    mediaPlayer = player;
}
