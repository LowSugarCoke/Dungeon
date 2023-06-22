#include "gameScene.h"

#include <string>
#include <iostream>

#include <QRandomGenerator>
#include <QTimer>

#include "level.h"
#include "resource.h"
#include "Dungeon.h"


static const std::pair<int, int> mazeSize{ 20,10 };

GameScene::GameScene(QObject* parent)
    : QGraphicsScene(parent)
    , mLifeText(new QGraphicsTextItem())
    , mLevelText(new QGraphicsTextItem())
    , mShurtkeyText(new QGraphicsTextItem())
    , mLevel(1)
    , mBrickSize(40)
{
    mLifeText->setDefaultTextColor(Qt::white); // Choose the color
    mLifeText->setFont(QFont("times", 16)); // Set the font and size
    addItem(mLifeText); // Add to the scene

    mLevelText->setDefaultTextColor(Qt::white); // Choose the color
    mLevelText->setFont(QFont("times", 16)); // Set the font and size
    addItem(mLevelText); // Add to the scene

    mShurtkeyText->setDefaultTextColor(Qt::white); // Choose the color
    mShurtkeyText->setFont(QFont("times", 16)); // Set the font and size
    mShurtkeyText->setPlainText(QString("Button Y => Next Level     Button U => Save    Button I => Load    Button O => Win    Button P => Lose"));
    mShurtkeyText->setPos(1000, 10); // Place it in the top left corner
    addItem(mShurtkeyText); // Add to the scene


    mBackgroundItem = new QGraphicsPixmapItem();
    addItem(mBackgroundItem);
    mOpacityEffect = new QGraphicsOpacityEffect();
    mOpacityEffect->setOpacity(1.0);

    mBackgroundItem->setGraphicsEffect(mOpacityEffect);
}

void GameScene::updateLifeText(int life) {
    mLifeText->setPlainText(QString("Life: %1").arg(life));
    mLifeText->setPos(100, 10); // Place it in the top left corner
}

void GameScene::updateLevelText(QString level) {
    mLevelText->setPlainText(QString("Level: %1").arg(level));
    mLevelText->setPos(200, 10); // Place it in the top left corner
}

void GameScene::setSceneImg(const QString& kSceneImg) {
    QImage backgroundImage(kSceneImg);
    setBackgroundBrush(QBrush(backgroundImage));
}
void GameScene::callLoad() {
    cleanData();
    static_cast<Dungeon*>(parent())->load();
}

void GameScene::loadData(History history) {
    QImage brickImage(UIResource::kBrickImg);

    // Adjust the size of the pixmap to fit your screen resolution
    int mBrickSize = 40;  // Adjust this to get your desired brick size
    QPixmap scaledBrickImg = QPixmap::fromImage(brickImage).scaled(mBrickSize, mBrickSize, Qt::KeepAspectRatio);

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
                mBricks.push_back(brick);
            }
        }
    }

    // Add the mHero to the scene
    mHero->setPos(history.heroPos.first * mBrickSize + offsetX, history.heroPos.second * mBrickSize + offsetY);
    mHero->setStartPos({ history.heroPos.first * mBrickSize + offsetX, history.heroPos.second * mBrickSize + offsetY });
    mHero->setLife(history.heroLife);

    for (int i = 0; i < history.trapPos.size(); i++) {
        Trap* trap = new Trap();
        mTraps.push_back(trap);
        trap->setImg(UIResource::kTrap);
        trap->setPos(history.trapPos[i].first * mBrickSize + offsetX, history.trapPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(trap);
    }

    for (int i = 0; i < history.potionPos.size(); i++) {
        Potion* potion = new Potion();
        mPotions.push_back(potion);
        potion->setImg(UIResource::kPotion);
        potion->setPos(history.potionPos[i].first * mBrickSize + offsetX, history.potionPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(potion);
    }

    for (int i = 0; i < history.superPotionPos.size(); i++) {
        SuperPotion* superPotion = new SuperPotion();
        mSuperPotions.push_back(superPotion);
        superPotion->setImg(UIResource::kSuperPotion);
        superPotion->setPos(history.superPotionPos[i].first * mBrickSize + offsetX, history.superPotionPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(superPotion);
    }

    mRemainingCollections = history.collectionPos.size();
    for (int i = 0; i < history.collectionPos.size(); i++) {
        Collection* collection = new Collection();
        mCollections.push_back(collection);
        collection->setImg(UIResource::kStar);
        collection->setPos(history.collectionPos[i].first * mBrickSize + offsetX, history.collectionPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(collection);
    }

    // Create the mMonsters based on the difficulty level
    for (int i = 0; i < history.monsterPos.size(); i++) {
        Monster* monster = new Monster();
        mMonsters.push_back(monster);
        monster->setMonsterImg(UIResource::kMonster);
        // Set the step size to be the same as the brick size
        monster->setStepSize(mBrickSize);
        monster->setPos(history.monsterPos[i].first * mBrickSize + offsetX, history.monsterPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(monster);

        // Setup a timer to move the monster every 1 second
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, monster, &Monster::randomMove);
        timer->start(history.monsterSpeed);
    }

    // Create the mDragons based on the difficulty level

    for (int i = 0; i < history.dragonPos.size(); i++) {
        Dragon* dragon = new Dragon(mHero);
        mDragons.push_back(dragon);
        dragon->setDragonImg(UIResource::kDragon);
        // Set the step size to be the same as the brick size
        dragon->setStepSize(mBrickSize);
        dragon->setZValue(1);
        dragon->setPos(history.dragonPos[i].first * mBrickSize + offsetX, history.dragonPos[i].second * mBrickSize + offsetY);
        // Add the monster to the scene
        this->addItem(dragon);

        // Setup a timer to move the monster every 1 second
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, dragon, &Dragon::randomMove);
        timer->start(history.dragonSpeed);
    }

    mLevel = history.level;
    updateLevelText(QString::number(history.level));
    updateLifeText(mHero->getLife());

    mHero->startInvincibleMode(2000);
}

void GameScene::saveData() {
    int mBrickSize = 40;

    // Calculate the offset to center the map
    int offsetX = 140;
    int offsetY = 70;

    // Create a new History object and fill it with current game state
    History kHistory;

    kHistory.maze = mMaze;
    kHistory.level = mLevel;
    kHistory.heroPos = { int(mHero->x() - offsetX) / mBrickSize, int(mHero->y() - offsetY) / mBrickSize };
    kHistory.heroLife = mHero->getLife();

    for (const auto& monster : mMonsters) {
        kHistory.monsterPos.push_back({ int(monster->x() - offsetX) / mBrickSize, int(monster->y() - offsetY) / mBrickSize });
    }
    kHistory.monsterSpeed = mMonsterSpeed;

    for (const auto& dragon : mDragons) {
        kHistory.dragonPos.push_back({ int(dragon->x() - offsetX) / mBrickSize, int(dragon->y() - offsetY) / mBrickSize });
    }
    kHistory.dragonSpeed = mDragonSpeed;

    for (const auto& collection : mCollections) {
        if (collection->isVisible()) {
            kHistory.collectionPos.push_back({ int(collection->x() - offsetX) / mBrickSize, int(collection->y() - offsetY) / mBrickSize });
        }
    }

    for (const auto& potion : mPotions) {
        if (potion->isVisible()) {
            kHistory.potionPos.push_back({ int(potion->x() - offsetX) / mBrickSize, int(potion->y() - offsetY) / mBrickSize });
        }
    }

    for (const auto& superPotion : mSuperPotions) {
        if (superPotion->isVisible()) {
            kHistory.superPotionPos.push_back({ int(superPotion->x() - offsetX) / mBrickSize, int(superPotion->y() - offsetY) / mBrickSize });
        }
    }

    for (const auto& trap : mTraps) {
        if (trap->isVisible()) {
            kHistory.trapPos.push_back({ int(trap->x() - offsetX) / mBrickSize, int(trap->y() - offsetY) / mBrickSize });
        }
    }

    // Save the History object using the DataHandler
    mDataHandler->save(kHistory);
}


void GameScene::generatorRandomMap(const QString& kBrickImg, const Level::LevelElement& kLevelElement) {
    mRemainingCollections = kLevelElement.starCount;
    generateMaze(kBrickImg, kLevelElement);
    placeHero();
    placeItems(mTraps, kLevelElement.trapCount, UIResource::kTrap);
    placeItems(mPotions, kLevelElement.potionCount, UIResource::kPotion);
    placeItems(mSuperPotions, kLevelElement.superPotionCount, UIResource::kSuperPotion);
    placeItems(mCollections, kLevelElement.starCount, UIResource::kStar);
    placeMonster(kLevelElement.monsterCount, kLevelElement.monsterspeed);
    placeDragon(kLevelElement.dragonCount, kLevelElement.dragonSpeed);
    updateTextAndHero(kLevelElement);
}

void GameScene::decreaseCollectionCount() {
    --mRemainingCollections;
}
bool GameScene::isAllCollectionsCollected() const { return mRemainingCollections == 0; }
void GameScene::nextLevel() {
    mLevel++;

    cleanData();

    // Save the current Hero's life.
    mHeroLife = mHero->getLife();

    if (mLevel != 11) {
        static_cast<Dungeon*>(parent())->nextLevel();
    }
    else {
        mLevel = 1;
        static_cast<Dungeon*>(parent())->win();
    }
}

void GameScene::lose() {
    cleanData();
    static_cast<Dungeon*>(parent())->lose();
}

void GameScene::setHero(Hero* mHero) {
    this->mHero = mHero;
    this->addItem(mHero);
}


void GameScene::setDataHanlder(std::shared_ptr<DataHandler> dataHandler) {
    mDataHandler = dataHandler;
}


void GameScene::setLevel(const int& kLevel) {
    mLevel = kLevel;
}


void GameScene::cleanData() {
    for (auto b : mBricks) {
        this->removeItem(b);
    }
    mBricks.clear();

    for (auto m : mMonsters) {
        this->removeItem(m);
    }
    mMonsters.clear();

    for (auto c : mCollections) {
        this->removeItem(c);
    }
    mCollections.clear();

    for (auto t : mTraps) {
        this->removeItem(t);
    }
    mTraps.clear();

    for (auto p : mPotions) {
        this->removeItem(p);
    }
    mPotions.clear();

    for (auto p : mSuperPotions) {
        this->removeItem(p);
    }
    mSuperPotions.clear();

    for (auto d : mDragons) {
        this->removeItem(d);
    }
    mDragons.clear();
}


void GameScene::generateMaze(const QString& kBrickImg, const Level::LevelElement& kLevelElement) {
    MazeGenerator mMaze(mazeSize.first, mazeSize.second, kLevelElement);  // Create a 20x15 mMaze
    this->mMaze = mMaze.getMaze();
    QImage brickImage(kBrickImg);

    // Adjust the size of the pixmap to fit your screen resolution
    int mBrickSize = 40;  // Adjust this to get your desired brick size
    QPixmap scaledBrickImg = QPixmap::fromImage(brickImage).scaled(mBrickSize, mBrickSize, Qt::KeepAspectRatio);

    // Calculate the offset to center the map
    mOffSetX = (width() - mMaze.getWidth() * mBrickSize) / 2;
    mOffSetY = (height() - mMaze.getHeight() * mBrickSize) / 2 - 50;

    for (int i = 0; i < mMaze.getWidth(); ++i) {
        for (int j = 0; j < mMaze.getHeight(); ++j) {
            if (mMaze(i, j) == 1) {  // If the cell is a wall, create a brick
                BrickItem* brick = new BrickItem(nullptr);
                brick->setPixmap(scaledBrickImg);
                brick->setPos(mOffSetX + i * brick->pixmap().width(), mOffSetY + j * brick->pixmap().height());
                this->addItem(brick);
                mBricks.push_back(brick);
            }
        }
    }
}
void GameScene::placeHero() {

    // Try to place the mHero
    bool heroPlaced = false;
    while (!heroPlaced) {
        // Set the mHero's position to a random place in the scene
        int x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * mBrickSize + mOffSetX;
        int y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * mBrickSize + mOffSetY;

        mHero->setPos(x, y);

        // Check if the mHero is colliding with something
        if (mHero->collidingItems().isEmpty()) {
            mHero->setStartPos({ x,y });
            // If not, then the mHero is successfully placed
            heroPlaced = true;
        }
    }
}
void GameScene::placeMonster(int monsterCount, int monsterSpeed) {
    for (int i = 0; i < monsterCount; i++) {
        Monster* monster = new Monster();
        mMonsters.push_back(monster);
        monster->setMonsterImg(UIResource::kMonster);
        // Set the step size to be the same as the brick size
        monster->setStepSize(mBrickSize);

        // Add the monster to the scene
        this->addItem(monster);

        // Position the monster in a random location that doesn't collide with anything
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * mBrickSize + mOffSetX;
            y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * mBrickSize + mOffSetY;
            monster->setPos(x, y);
        } while (!monster->collidingItems().isEmpty());

        // Setup a timer to move the monster every 1 second
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, monster, &Monster::randomMove);
        timer->start(monsterSpeed);
    }
    mMonsterSpeed = monsterSpeed;
}
void GameScene::placeDragon(int dragonCount, int dragonSpeed) {
    for (int i = 0; i < dragonCount; i++) {
        Dragon* dragon = new Dragon(mHero);
        mDragons.push_back(dragon);
        dragon->setDragonImg(UIResource::kDragon);
        // Set the step size to be the same as the brick size
        dragon->setStepSize(mBrickSize);
        dragon->setZValue(1);
        // Add the monster to the scene
        this->addItem(dragon);

        // Position the monster in a random location that doesn't collide with anything
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * mBrickSize + mOffSetX;
            y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * mBrickSize + mOffSetY;
            dragon->setPos(x, y);
        } while (x <= 140 || x >= 1000 || y <= 70 || y >= 700);

        // Setup a timer to move the monster every 1 second
        QTimer* timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, dragon, &Dragon::randomMove);
        timer->start(dragonSpeed);
    }
    mDragonSpeed = dragonSpeed;
}

template<typename T>
void GameScene::placeItems(std::vector<T*>& items, int count, const QString& imageResource) {
    for (int i = 0; i < count; i++) {
        T* item = new T();
        items.push_back(item);

        item->setImg(imageResource);

        this->addItem(item);

        // Position the item in a random location that doesn't collide with anything
        int x, y;
        do {
            x = QRandomGenerator::global()->bounded(mazeSize.first * 2) * mBrickSize + mOffSetX;
            y = QRandomGenerator::global()->bounded(mazeSize.second * 2) * mBrickSize + mOffSetY;
            item->setPos(x, y);
        } while (!item->collidingItems().isEmpty());
    }
}

void GameScene::updateTextAndHero(const Level::LevelElement& kLevelElement) {
    updateLevelText(QString::fromStdString(kLevelElement.level));
    updateLifeText(mHero->getLife());
    if (kLevelElement.level == "1") {
        mHero->startInvincibleMode(6000);
    }
    else {
        mHero->startInvincibleMode(2000);
    }
}
