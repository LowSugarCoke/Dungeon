#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include "ui_Dungeon.h"
#include "level.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"
#include "endingScene.h"


class Dungeon : public QMainWindow
{
    Q_OBJECT

public:
    Dungeon(QWidget* parent = Q_NULLPTR);
    void nextLevel();
    void win();
    void lose();
private:
    Ui::DungeonClass ui;
    void initUI();
    int heroLife;
    Level::LevelElement currentLevel;
    Hero* hero; // Add this line

    GameScene* scene;
    GameView* sceneView;
    EndingScene* endingScene;
};
