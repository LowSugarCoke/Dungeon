#pragma once

#include <QGraphicsScene>
#include <QSlider>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>

class MainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:
    MainMenuScene(QObject* parent = nullptr);
    QSlider* getVolumeSlider() const;
    void setSceneImg(const QString& kSceneImg);
    void fadeIn(int duration);
    void fadeOut(int duration);

private:
    QGraphicsPixmapItem* m_backgroundItem;
    QGraphicsOpacityEffect* m_opacityEffect;

private slots:
    void handleStartButton();
    void handleSettingsButton();
    void handleExitButton();



};
