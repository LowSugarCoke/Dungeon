#pragma once

#include <QGraphicsScene>

class BrickItem;
class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void generatorRandomMap(const QString& kBrickImg);


};
