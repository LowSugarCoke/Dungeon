

#include "MainMenuScene.h"
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QGraphicsLinearLayout>
#include <QGraphicsWidget>
#include <QtWidgets/QMainWindow>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

#include "resource.h"
#include "Dungeon.h"

MainMenuScene::MainMenuScene(QObject* parent)
    : QGraphicsScene(parent)
{
    m_backgroundItem = new QGraphicsPixmapItem();
    addItem(m_backgroundItem);
    m_opacityEffect = new QGraphicsOpacityEffect();
    m_opacityEffect->setOpacity(1.0);

    m_backgroundItem->setGraphicsEffect(m_opacityEffect);

    QGraphicsWidget* root = new QGraphicsWidget();
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical, root);
    root->setLayout(layout);
    root->resize(1920, 1080);
    addItem(root);

    root->setPos(700, 300);


    QPushButton* startButton = new QPushButton(QString::fromLocal8Bit("開始遊戲"));
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

    startButton->setMinimumSize(400, 120);
    startButton->setMaximumSize(400, 120);
    QGraphicsProxyWidget* startButtonProxy = addWidget(startButton);
    //startButtonProxy->resize(100, 30);
    layout->addItem(startButtonProxy);
    layout->setAlignment(startButtonProxy, Qt::AlignCenter);  // 設定對齊方式
    connect(startButton, &QPushButton::clicked, this, &MainMenuScene::handleStartButton);

    QPushButton* settingsButton = new QPushButton(QString::fromLocal8Bit("設定"));
    settingsButton->setStyleSheet(R"(
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
    settingsButton->setMinimumSize(400, 120);
    settingsButton->setMaximumSize(400, 120);
    QGraphicsProxyWidget* settingsButtonProxy = addWidget(settingsButton);
    layout->addItem(settingsButtonProxy);
    layout->setAlignment(settingsButtonProxy, Qt::AlignCenter);  // 設定對齊方式
    connect(settingsButton, &QPushButton::clicked, this, &MainMenuScene::handleSettingsButton);

    QPushButton* exitButton = new QPushButton(QString::fromLocal8Bit("結束遊戲"));
    exitButton->setStyleSheet(R"(
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
    exitButton->setMinimumSize(400, 120);
    exitButton->setMaximumSize(400, 120);
    QGraphicsProxyWidget* exitButtonProxy = addWidget(exitButton);
    layout->addItem(exitButtonProxy);
    layout->setAlignment(exitButtonProxy, Qt::AlignCenter);  // 設定對齊方式
    connect(exitButton, &QPushButton::clicked, this, &MainMenuScene::handleExitButton);
}

void MainMenuScene::handleStartButton() {
    static_cast<Dungeon*>(parent())->battle();
    mediaPlayer->mainMenu->stop();
    mediaPlayer->start->play();
}

void MainMenuScene::handleSettingsButton() {
    // 處理當"設定"按鈕被點擊時的邏輯
    static_cast<Dungeon*>(parent())->setting();
}

void MainMenuScene::handleExitButton() {
    // 處理當"結束遊戲"按鈕被點擊時的邏輯
    QApplication::quit();
}

void MainMenuScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    m_backgroundItem->setPixmap(backgroundImage);
}


void MainMenuScene::fadeIn(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainMenuScene::fadeOut(int duration) {
    QPropertyAnimation* animation = new QPropertyAnimation(m_opacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainMenuScene::setMedia(MediaPlayer* player) {
    mediaPlayer = player;
}
