#pragma once

#include <QGraphicsScene>

#include "mazeGenerator.h"
#include "collection.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"

class BrickItem;
class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject* parent = nullptr);
    void setSceneImg(const QString& kSceneImg);
    void generatorRandomMap(const QString& kBrickImg, const Level::LevelElement& kLevelElement);
    void updateLifeText(int life);
    void updateLevelText(QString level);

    void decreaseCollectionCount();
    bool isAllCollectionsCollected() const;
    void nextLevel();
    void setHero(Hero* hero);

private:
    int brickSize = 40;  // Save the size of your maze cells here
    QGraphicsTextItem* lifeText;
    QGraphicsTextItem* levelText;
    int remainingCollections;
    Hero* hero;
    int heroLife;
    int level;


};
