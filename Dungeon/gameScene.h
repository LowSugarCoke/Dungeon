#pragma once

#include <QGraphicsScene>

#include "mazeGenerator.h"
#include "collection.h"
#include "hero.h"
#include "gameScene.h"
#include "gameView.h"
#include "brickItem.h"
#include "trap.h"
#include "potion.h"
#include "superPotion.h"
#include "dragon.h"
#include "history.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>

class Monster;
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
	void lose();
	void setHero(Hero* hero);
	int level;
	void loadData(History history);
	void callLoad();
	void saveData();

private:
	int brickSize = 40;  // Save the size of your maze cells here
	QGraphicsTextItem* lifeText;
	QGraphicsTextItem* levelText;
	int remainingCollections;
	Hero* hero;
	int heroLife;
	int monsterSpeed;
	int dragonSpeed;

	QGraphicsPixmapItem* m_backgroundItem;
	QGraphicsOpacityEffect* m_opacityEffect;
	std::vector<Monster*> monsters;
	std::vector<Dragon*> dragons;
	std::vector<BrickItem*> bricks;
	std::vector<Collection*> collections;
	std::vector<Trap*> traps;
	std::vector<Potion*> potions;
	std::vector<SuperPotion*> superPotions;
	std::vector<std::vector<int>> maze;
};
