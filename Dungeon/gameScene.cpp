#include "gameScene.h"

#include <QRandomGenerator>
#include <QTimer>

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

void GameScene::generatorRandomMap(const QString& kBrickImg, const Level::LevelElement& kLevelElement) {
	MazeGenerator maze(mazeSize.first, mazeSize.second, kLevelElement);  // Create a 20x15 maze

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
	this->addItem(hero);

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

	// Create the dragons based on the difficulty level
	int dragonCount = kLevelElement.dragonCount;
	for (int i = 0; i < dragonCount; i++) {
		Dragon* dragon = new Dragon(hero);
		dragons.push_back(dragon);
		dragon->setDragonImg(UIResource::kDragon);
		// Set the step size to be the same as the brick size
		dragon->setStepSize(brickSize);

		// Add the monster to the scene
		this->addItem(dragon);

		// Position the monster in a random location that doesn't collide with anything
		int x, y;
		do {
			x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * brickSize + offsetX;
			y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * brickSize + offsetY;
			dragon->setPos(x, y);
		} while (x >= 140 && x <= 1600 && y >= 70 && y <= 800);

		// Setup a timer to move the monster every 1 second
		QTimer* timer = new QTimer();
		QObject::connect(timer, &QTimer::timeout, dragon, &Dragon::randomMove);
		timer->start(kLevelElement.dragonSpeed);
	}

	updateLevelText(kLevelElement.level);
	updateLifeText(hero->getLife());
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
	}

	for (auto m : monsters) {
		this->removeItem(m);
	}

	for (auto c : collections) {
		this->removeItem(c);
	}

	for (auto t : traps) {
		this->removeItem(t);
	}

	for (auto p : potions) {
		this->removeItem(p);
	}

	for (auto p : superPotions) {
		this->removeItem(p);
	}

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
	}

	for (auto m : monsters) {
		this->removeItem(m);
	}

	for (auto c : collections) {
		this->removeItem(c);
	}

	for (auto t : traps) {
		this->removeItem(t);
	}

	for (auto p : potions) {
		this->removeItem(p);
	}

	for (auto p : superPotions) {
		this->removeItem(p);
	}

	static_cast<Dungeon*>(parent())->lose();
}

void GameScene::setHero(Hero* hero) {
	this->hero = hero;
}