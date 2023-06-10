#pragma once

#include <memory>

#include <QtWidgets/QMainWindow>
#include "ui_Dungeon.h"


class Dungeon : public QMainWindow
{
    Q_OBJECT

public:
    Dungeon(QWidget* parent = Q_NULLPTR);

private:
    Ui::DungeonClass ui;
    void initUI();
};
