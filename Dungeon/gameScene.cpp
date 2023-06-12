#include "gameScene.h"

#include <QRandomGenerator>
#include <QTimer>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "brickItem.h"
#include "hero.h"
#include "monster.h"
#include "level.h"
#include "resource.h"
#include "collection.h"
#include "potion.h"
#include "superPotion.h"
#include "Dungeon.h"
#include "trap.h"

static const std::pair<int, int> mazeSize{ 20,10 };

GameScene::GameScene(QObject* parent)
	: QGraphicsScene(parent)
	, lifeText(new QGraphicsTextItem())
	, levelText(new QGraphicsTextItem())
	, level(1)
{
	lifeText->setDefaultTextColor(Qt::white); // Choose the color
	lifeText->setFont(QFont("times", 16)); // Set the font and size
	addItem(lifeText); // Add to the scene

	levelText->setDefaultTextColor(Qt::white); // Choose the color
	levelText->setFont(QFont("times", 16)); // Set the font and size
	addItem(levelText); // Add to the scene

	m_backgroundItem = new QGraphicsPixmapItem();
	addItem(m_backgroundItem);
	m_opacityEffect = new QGraphicsOpacityEffect();
	m_opacityEffect->setOpacity(1.0);

	m_backgroundItem->setGraphicsEffect(m_opacityEffect);
}

void GameScene::updateLifeText(int life) {
	lifeText->setPlainText(QString("Life: %1").arg(life));
	lifeText->setPos(20, 10); // Place it in the top left corner
}

void GameScene::updateLevelText(QString level) {
	levelText->setPlainText(QString("Level: %1").arg(level));
	levelText->setPos(100, 10); // Place it in the top left corner
}

void GameScene::setSceneImg(const QString& kSceneImg) {
	QImage backgroundImage(kSceneImg);
	setBackgroundBrush(QBrush(backgroundImage));
}
void GameScene::callLoad() {
	for (auto b : bricks) {
		this->removeItem(b);
		//delete b;
	}
	bricks.clear();

	for (auto m : monsters) {
		this->removeItem(m);
		//delete m;
	}
	monsters.clear();

	for (auto c : collections) {
		this->removeItem(c);
		//delete c;
	}
	collections.clear();

	for (auto t : traps) {
		this->removeItem(t);
		//delete t;
	}
	traps.clear();

	for (auto p : potions) {
		this->removeItem(p);
		//delete p;
	}
	potions.clear();

	for (auto p : superPotions) {
		this->removeItem(p);
		//delete p;
	}
	superPotions.clear();

	for (auto d : dragons) {
		this->removeItem(d);
		//delete d;
	}
	dragons.clear();

	static_cast<Dungeon*>(parent())->load();
}

void GameScene::loadData(History history) {
	QImage brickImage(UIResource::kBrickImg);

	// Adjust the size of the pixmap to fit your screen resolution
	int brickSize = 40;  // Adjust this to get your desired brick size
	QPixmap scaledBrickImg = QPixmap::fromImage(brickImage).scaled(brickSize, brickSize, Qt::KeepAspectRatio);

	// Calculate the offset to center the map
	int offsetX = 140;
	int offsetY = 70;

	for (int i = 0; i < (mazeSize.first * 2 + 1); ++i) {
		for (int j = 0; j < (mazeSize.second * 2 + 1); ++j) {
			if (history.maze[j][i] == 1) {  // If the cell is a wall, create a brick
				BrickItem* brick = new BrickItem(nullptr);
				brick->setPixmap(scaledBrickImg);
				brick->setPos(offsetX + i * brick->pixmap().width(), offsetY + j * brick->pixmap().height());
				this->addItem(brick);
				bricks.push_back(brick);
			}
		}
	}

	// Add the hero to the scene
	hero->setPos(history.heroPos.first * brickSize + offsetX, history.heroPos.second * brickSize + offsetY);
	hero->setStartPos({ history.heroPos.first * brickSize + offsetX, history.heroPos.second * brickSize + offsetY });
	hero->setLife(history.heroLife);

	for (int i = 0; i < history.trapPos.size(); i++) {
		Trap* trap = new Trap();
		traps.push_back(trap);
		trap->setTrapImg(UIResource::kTrap);
		trap->setPos(history.trapPos[i].first * brickSize + offsetX, history.trapPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(trap);
	}

	for (int i = 0; i < history.potionPos.size(); i++) {
		Potion* potion = new Potion();
		potions.push_back(potion);
		potion->setPotionImg(UIResource::kPotion);
		potion->setPos(history.potionPos[i].first * brickSize + offsetX, history.potionPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(potion);
	}

	for (int i = 0; i < history.superPotionPos.size(); i++) {
		SuperPotion* superPotion = new SuperPotion();
		superPotions.push_back(superPotion);
		superPotion->setPotionImg(UIResource::kSuperPotion);
		superPotion->setPos(history.superPotionPos[i].first * brickSize + offsetX, history.superPotionPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(superPotion);
	}

	remainingCollections = history.collectionPos.size();
	for (int i = 0; i < history.collectionPos.size(); i++) {
		Collection* collection = new Collection();
		collections.push_back(collection);
		collection->setCollectionImg(UIResource::kStar);
		collection->setPos(history.collectionPos[i].first * brickSize + offsetX, history.collectionPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(collection);
	}

	// Create the monsters based on the difficulty level
	for (int i = 0; i < history.monsterPos.size(); i++) {
		Monster* monster = new Monster();
		monsters.push_back(monster);
		monster->setMonsterImg(UIResource::kMonster);
		// Set the step size to be the same as the brick size
		monster->setStepSize(brickSize);
		monster->setPos(history.monsterPos[i].first * brickSize + offsetX, history.monsterPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(monster);

		// Setup a timer to move the monster every 1 second
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, monster, &Monster::randomMove);
		timer->start(history.monsterSpeed);;
	}

	// Create the dragons based on the difficulty level

	for (int i = 0; i < history.dragonPos.size(); i++) {
		Dragon* dragon = new Dragon(hero);
		dragons.push_back(dragon);
		dragon->setDragonImg(UIResource::kDragon);
		// Set the step size to be the same as the brick size
		dragon->setStepSize(brickSize);
		dragon->setZValue(1);
		dragon->setPos(history.dragonPos[i].first * brickSize + offsetX, history.dragonPos[i].second * brickSize + offsetY);
		// Add the monster to the scene
		this->addItem(dragon);

		// Setup a timer to move the monster every 1 second
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, dragon, &Dragon::randomMove);
		timer->start(history.dragonSpeed);
	}

	level = history.level;
	updateLevelText(QString::number(history.level));
	updateLifeText(hero->getLife());

	//hero->startInvincibleMode(2000);
}

void GameScene::saveData() {
	int brickSize = 40;

	// Calculate the offset to center the map
	int offsetX = 140;
	int offsetY = 70;

	std::string filename = "data.txt";
	std::ofstream file(filename);

	if (!file) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}

	// Save maze
	for (size_t i = 0; i < maze[0].size(); ++i) {
		for (size_t j = 0; j < maze.size(); ++j) {
			file << maze[j][i];
			if (j != maze.size() - 1) {
				file << ",";
			}
		}
		file << "\n";
	}

	// Save level
	file << "Level " << level << "\n";

	// Save hero
	int ss = hero->x();
	file << "Hero " << int(hero->x() - offsetX) / brickSize << " " << int(hero->y() - offsetY) / brickSize << " " << hero->getLife() << "\n";

	// Save monsters
	file << "Monster ";
	for (const auto& monster : monsters) {
		file << int(monster->x() - offsetX) / brickSize << " " << int(monster->y() - offsetY) / brickSize << " ";
	}
	file << "\n";

	// Save MonsterSpeed
	file << "MonsterSpeed  " << monsterSpeed << "\n";

	// Save dragons
	file << "Dragon ";
	for (const auto& dragon : dragons) {
		file << int(dragon->x() - offsetX) / brickSize << " " << int(dragon->y() - offsetY) / brickSize << " ";
	}
	file << "\n";

	// Save DragonSpeed
	file << "DragonSpeed   " << dragonSpeed << "\n";

	// Save collections
	file << "Collection  ";
	for (const auto& collection : collections) {
		if (collection->isVisible()) {
			file << int(collection->x() - offsetX) / brickSize << " " << int(collection->y() - offsetY) / brickSize << " ";
		}
	}
	file << "\n";

	// Save Potion
	file << "Potion  ";
	for (const auto& potion : potions) {
		if (potion->isVisible()) {
			file << int(potion->x() - offsetX) / brickSize << " " << int(potion->y() - offsetY) / brickSize << " ";
		}
	}
	file << "\n";

	// Save super potions
	file << "SuperPotion ";
	for (const auto& superPotion : superPotions) {
		if (superPotion->isVisible()) {
			file << int(superPotion->x() - offsetX) / brickSize << " " << int(superPotion->y() - offsetY) / brickSize << " ";
		}
	}
	file << "\n";

	file << "Trap  ";
	for (const auto& trap : traps) {
		if (trap->isVisible()) {
			file << int(trap->x() - offsetX) / brickSize << " " << int(trap->y() - offsetY) / brickSize << " ";
		}
	}

	file.close();
}

void GameScene::generatorRandomMap(const QString& kBrickImg, const Level::LevelElement& kLevelElement) {
	MazeGenerator maze(mazeSize.first, mazeSize.second, kLevelElement);  // Create a 20x15 maze
	this->maze = maze.getMaze();
	QImage brickImage(kBrickImg);

	// Adjust the size of the pixmap to fit your screen resolution
	int brickSize = 40;  // Adjust this to get your desired brick size
	QPixmap scaledBrickImg = QPixmap::fromImage(brickImage).scaled(brickSize, brickSize, Qt::KeepAspectRatio);

	// Calculate the offset to center the map
	int offsetX = (width() - maze.getWidth() * brickSize) / 2;
	int offsetY = (height() - maze.getHeight() * brickSize) / 2 - 50;

	for (int i = 0; i < maze.getWidth(); ++i) {
		for (int j = 0; j < maze.getHeight(); ++j) {
			if (maze(i, j) == 1) {  // If the cell is a wall, create a brick
				BrickItem* brick = new BrickItem(nullptr);
				brick->setPixmap(scaledBrickImg);
				brick->setPos(offsetX + i * brick->pixmap().width(), offsetY + j * brick->pixmap().height());
				this->addItem(brick);
				bricks.push_back(brick);
			}
		}
	}

	// Add the hero to the scene
	//this->addItem(hero);

	// Try to place the hero
	bool heroPlaced = false;
	while (!heroPlaced) {
		// Set the hero's position to a random place in the scene
		int x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
		int y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;

		hero->setPos(x, y);

		// Check if the hero is colliding with something
		if (hero->collidingItems().isEmpty()) {
			hero->setStartPos({ x,y });
			// If not, then the hero is successfully placed
			heroPlaced = true;
		}
	}

	for (int i = 0; i < kLevelElement.trapCount; i++) {
		Trap* trap = new Trap();
		traps.push_back(trap);
		trap->setTrapImg(UIResource::kTrap);

		// Add the monster to the scene
		this->addItem(trap);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;

			trap->setPos(x, y);
		} while (!trap->collidingItems().isEmpty());
	}

	for (int i = 0; i < kLevelElement.potionCount; i++) {
		Potion* potion = new Potion();
		potions.push_back(potion);
		potion->setPotionImg(UIResource::kPotion);

		// Add the monster to the scene
		this->addItem(potion);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			potion->setPos(x, y);
		} while (!potion->collidingItems().isEmpty());
	}

	for (int i = 0; i < kLevelElement.superPotionCount; i++) {
		SuperPotion* superPotion = new SuperPotion();
		superPotions.push_back(superPotion);
		superPotion->setPotionImg(UIResource::kSuperPotion);

		// Add the monster to the scene
		this->addItem(superPotion);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			superPotion->setPos(x, y);
		} while (!superPotion->collidingItems().isEmpty());
	}

	remainingCollections = kLevelElement.starCount;
	for (int i = 0; i < kLevelElement.starCount; i++) {
		Collection* collection = new Collection();
		collections.push_back(collection);
		collection->setCollectionImg(UIResource::kStar);

		// Add the monster to the scene
		this->addItem(collection);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			collection->setPos(x, y);
		} while (!collection->collidingItems().isEmpty());
	}

	// Create the monsters based on the difficulty level
	int monsterCount = kLevelElement.monsterCount;
	for (int i = 0; i < monsterCount; i++) {
		Monster* monster = new Monster();
		monsters.push_back(monster);
		monster->setMonsterImg(UIResource::kMonster);
		// Set the step size to be the same as the brick size
		monster->setStepSize(brickSize);

		// Add the monster to the scene
		this->addItem(monster);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			monster->setPos(x, y);
		} while (!monster->collidingItems().isEmpty());

		// Setup a timer to move the monster every 1 second
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, monster, &Monster::randomMove);
		timer->start(kLevelElement.monsterspeed);
	}
	monsterSpeed = kLevelElement.monsterspeed;

	// Create the dragons based on the difficulty level
	int dragonCount = kLevelElement.dragonCount;
	for (int i = 0; i < dragonCount; i++) {
		Dragon* dragon = new Dragon(hero);
		dragons.push_back(dragon);
		dragon->setDragonImg(UIResource::kDragon);
		// Set the step size to be the same as the brick size
		dragon->setStepSize(brickSize);
		dragon->setZValue(1);
		// Add the monster to the scene
		this->addItem(dragon);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			dragon->setPos(x, y);
		} while (x >= 140 && x <= 1400 && y >= 70 && y <= 700);

		// Setup a timer to move the monster every 1 second
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, dragon, &Dragon::randomMove);
		timer->start(kLevelElement.dragonSpeed);
	}
	dragonSpeed = kLevelElement.dragonSpeed;

	updateLevelText(kLevelElement.level);
	updateLifeText(hero->getLife());
	if (kLevelElement.level == Level::kLevel1.level) {
		hero->startInvincibleMode(6000);
	}
	else {
		hero->startInvincibleMode(2000);
	}
}

void GameScene::decreaseCollectionCount() {
	--remainingCollections;
}
bool GameScene::isAllCollectionsCollected() const { return remainingCollections == 0; }
void GameScene::nextLevel() {
	level++;
	//this->removeItem(hero);
	//this->clear();

	for (auto b : bricks) {
		this->removeItem(b);
		//delete b;
	}
	bricks.clear();

	for (auto m : monsters) {
		this->removeItem(m);
		//delete m;
	}
	monsters.clear();

	for (auto c : collections) {
		this->removeItem(c);
		//delete c;
	}
	collections.clear();

	for (auto t : traps) {
		this->removeItem(t);
		//delete t;
	}
	traps.clear();

	for (auto p : potions) {
		this->removeItem(p);
		//delete p;
	}
	potions.clear();

	for (auto p : superPotions) {
		this->removeItem(p);
		//delete p;
	}
	superPotions.clear();

	for (auto d : dragons) {
		this->removeItem(d);
		//delete d;
	}
	dragons.clear();

	// Save the current Hero's life.
	heroLife = hero->getLife();

	if (level != 11) {
		// Continue to the next level.
		static_cast<Dungeon*>(parent())->nextLevel();
	}
	else {
		level = 1;
		static_cast<Dungeon*>(parent())->win();
	}
}

void GameScene::lose() {
	for (auto b : bricks) {
		this->removeItem(b);
		//delete b;
	}
	bricks.clear();

	for (auto m : monsters) {
		this->removeItem(m);
		//delete m;
	}
	monsters.clear();

	for (auto c : collections) {
		this->removeItem(c);
		//delete c;
	}
	collections.clear();

	for (auto t : traps) {
		this->removeItem(t);
		//delete t;
	}
	traps.clear();

	for (auto p : potions) {
		this->removeItem(p);
		//delete p;
	}
	potions.clear();

	for (auto p : superPotions) {
		this->removeItem(p);
		//delete p;
	}
	superPotions.clear();

	for (auto d : dragons) {
		this->removeItem(d);
		//delete d;
	}
	dragons.clear();

	static_cast<Dungeon*>(parent())->lose();
}

void GameScene::setHero(Hero* hero) {
	this->hero = hero;
	this->addItem(hero);
}