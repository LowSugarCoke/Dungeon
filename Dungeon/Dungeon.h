﻿#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include "ui_Dungeon.h"
#include "level.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"
#include "endingScene.h"
#include "mainMenuScene.h"
#include "mediaPlayer.h"
#include "settingScene.h"

class Dungeon : public QMainWindow
{
    Q_OBJECT

public:
    Dungeon(QWidget* parent = Q_NULLPTR);
    void nextLevel();
    void win();
    void lose();
    void battle();
    void setting();
    void menu();
    void restart();
private:
    Ui::DungeonClass ui;

    int heroLife;
    Level::LevelElement currentLevel;
    Hero* hero; // Add this line

    GameScene* scene;
    GameView* sceneView;
    EndingScene* endingScene;
    MainMenuScene* menuScene;
    MediaPlayer* mediaPlayer;
    SettingScene* settingScene;
};
