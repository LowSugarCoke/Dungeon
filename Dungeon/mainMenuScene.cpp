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

// Constructor for the MainMenuScene class.
MainMenuScene::MainMenuScene(QObject* parent)
    : QGraphicsScene(parent)
{
    // Initialize and set up background item.
    mBackgroundItem = new QGraphicsPixmapItem();
    addItem(mBackgroundItem);
    mOpacityEffect = new QGraphicsOpacityEffect();
    mOpacityEffect->setOpacity(1.0);
    mBackgroundItem->setGraphicsEffect(mOpacityEffect);

    // Initialize and set up title item.
    mTitle = new QGraphicsPixmapItem();
    addItem(mTitle);
    mOpacityEffect = new QGraphicsOpacityEffect();
    mOpacityEffect->setOpacity(1.0);
    mTitle->setGraphicsEffect(mOpacityEffect);

    // Set image for title item.
    QPixmap backgroundImage(UIResource::kTitle);
    mTitle->setPixmap(backgroundImage);
    mTitle->setPos(50, 50);

    // Setup layout and root widget.
    QGraphicsWidget* root = new QGraphicsWidget();
    QGraphicsLinearLayout* layout = new QGraphicsLinearLayout(Qt::Vertical, root);
    root->setLayout(layout);
    root->resize(1920, 1080);
    addItem(root);
    root->setPos(700, 300);

    // Setup the start button and its properties.
    mStartButton = setupButton(QString::fromLocal8Bit("開始遊戲"), layout);
    connect(mStartButton, &QPushButton::clicked, this, &MainMenuScene::handleStartButton);

    // Setup the loading button and its properties.
    mLoadingButton = setupButton(QString::fromLocal8Bit("讀取存檔"), layout);
    connect(mLoadingButton, &QPushButton::clicked, this, &MainMenuScene::handleLoadingButton);

    // Setup the settings button and its properties.
    mSettingsButton = setupButton(QString::fromLocal8Bit("設定"), layout);
    connect(mSettingsButton, &QPushButton::clicked, this, &MainMenuScene::handleSettingsButton);

    // Setup the exit button and its properties.
    mExitButton = setupButton(QString::fromLocal8Bit("結束遊戲"), layout);
    connect(mExitButton, &QPushButton::clicked, this, &MainMenuScene::handleExitButton);
}

// Function to handle the start button click.
void MainMenuScene::handleStartButton() {
    static_cast<Dungeon*>(parent())->intro();
}

// Function to handle the loading button click.
void MainMenuScene::handleLoadingButton() {
    static_cast<Dungeon*>(parent())->load();
}

// Function to handle the settings button click.
void MainMenuScene::handleSettingsButton() {
    static_cast<Dungeon*>(parent())->setting();
}

// Function to handle the exit button click.
void MainMenuScene::handleExitButton() {
    QApplication::quit();
}

// Function to set the image of the scene.
void MainMenuScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(sceneRect().size().toSize(), Qt::KeepAspectRatioByExpanding);
    mBackgroundItem->setPixmap(backgroundImage);
}

// Function to animate a fade in over the specified duration.
void MainMenuScene::fadeIn(int duration) {
    mStartButton->show();
    mSettingsButton->show();
    mExitButton->show();
    QPropertyAnimation* animation = new QPropertyAnimation(mOpacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// Function to animate a fade out over the specified duration.
void MainMenuScene::fadeOut(int duration) {
    mStartButton->hide();
    mSettingsButton->hide();
    mExitButton->hide();
    QPropertyAnimation* animation = new QPropertyAnimation(mOpacityEffect, "opacity");
    animation->setDuration(duration);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// Helper function to setup a QPushButton with common properties.
QPushButton* MainMenuScene::setupButton(const QString& buttonText, QGraphicsLinearLayout* layout) {
    QPushButton* button = new QPushButton(buttonText);
    button->setStyleSheet(R"(
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

    button->setMinimumSize(400, 120);
    button->setMaximumSize(400, 120);
    QGraphicsProxyWidget* buttonProxy = addWidget(button);
    layout->addItem(buttonProxy);
    layout->setAlignment(buttonProxy, Qt::AlignCenter);

    return button;
}
