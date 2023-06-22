#pragma once

#include <QGraphicsScene>
#include <QSlider>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QPushButton>


class MainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainMenuScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);


private:
    QGraphicsPixmapItem* m_backgroundItem;
    QGraphicsOpacityEffect* m_opacityEffect;


    QPushButton* startButton;
    QPushButton* settingsButton;
    QPushButton* loadingButton;
    QPushButton* exitButton;
    QGraphicsPixmapItem* m_title;

private slots:
    void handleStartButton();
    void handleLoadingButton();
    void handleSettingsButton();
    void handleExitButton();
};
