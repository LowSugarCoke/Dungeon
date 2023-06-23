#include "Dungeon.h"

#include <iostream>

#include <QScreen>
#include <QTimer>

#include "resource.h"
#include "levelParser.h"

Dungeon::Dungeon(QWidget* parent)
    : QMainWindow(parent)
    , mHero(new Hero())
    , mDataHandler(std::make_shared<DataHandler>())
    , mMediaPlayer(std::make_shared<MediaPlayer>())
{
    ui.setupUi(this);
    setWindowIcon(QIcon(UIResource::kLogo));

    LevelParser levelParser;
    mLevelData = levelParser.parser(DataResource::kLevel.toStdString());
    mCurrentLevel = mLevelData[0];

    mHero->setPotionSound(mMediaPlayer->potion);
    mHero->setMonsterSound(mMediaPlayer->monster);
    mHero->setCollectionSound(mMediaPlayer->collection);
    mHero->setTrapSound(mMediaPlayer->trap);
    mHero->setSuperPotionSound(mMediaPlayer->superPotion);
    mHero->setDrangonSound(mMediaPlayer->start);
    mHero->setHeroImg(UIResource::kHero);

    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    this->resize(screenGeometry.width(), screenGeometry.height());

    mGameScene = new GameScene(this);
    mGameScene->setHero(mHero);
    mGameScene->setSceneImg(UIResource::kSceneImg);
    mGameScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());

    mSceneView = new GameView(mGameScene, this);

    mEndingScene = new EndingScene(this);
    mEndingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());

    mMenuScene = new MainMenuScene(this);
    mMenuScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());

    mSettingScene = new SettingScene(mMediaPlayer, this);
    mSettingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    mSettingScene->setSceneImg(UIResource::kMenu);

    mIntroScene = new IntroScene(this);
    mIntroScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
    mIntroScene->setSceneImg(UIResource::kMenu);
    mIntroScene->setMedia(mMediaPlayer);

    menu();
}

Dungeon::~Dungeon()
{
    delete mHero;
    delete mGameScene;
    delete mSceneView;
    delete mEndingScene;
    delete mMenuScene;
    delete mSettingScene;
    delete mIntroScene;
}


void Dungeon::load() {
    mMediaPlayer->mainMenu->stop();
    mMediaPlayer->battle->stop();
    mMediaPlayer->battle->play();

    auto history = mDataHandler->load(DataResource::kData.toStdString());
    mCurrentLevel = mLevelData[history.level - 1];
    mGameScene->loadData(history);
    mSceneView->setScene(mGameScene);
    mHero->setFocus();
}

void Dungeon::intro() {
    mIntroScene->fadeIn(0);
    mSceneView->setScene(mIntroScene);
    mIntroScene->startStory();
    this->setCentralWidget(mSceneView);
}

void Dungeon::setting() {
    mSceneView->setScene(mSettingScene);
}

void Dungeon::menu() {
    mMenuScene->setSceneImg(UIResource::kMenu);
    mMenuScene->fadeIn(0);
    mMediaPlayer->endingWin->stop();
    mMediaPlayer->endingLose->stop();
    mMediaPlayer->mainMenu->play();
    mSceneView->setScene(mMenuScene);
    this->setCentralWidget(mSceneView);
}

void Dungeon::win() {
    mMediaPlayer->battle->stop();
    mMediaPlayer->endingWin->play();

    mEndingScene->setSceneImg(UIResource::kWin);
    mSceneView->setScene(mEndingScene);
    mEndingScene->fadeIn(1000);
    mEndingScene->setMessage("You Win");
    this->setCentralWidget(mSceneView);
}

void Dungeon::lose() {
    mMediaPlayer->battle->stop();
    mMediaPlayer->endingLose->play();

    mEndingScene->setSceneImg(UIResource::kLose);
    mSceneView->setScene(mEndingScene);
    mEndingScene->fadeIn(1000);
    mEndingScene->setMessage("You Lose");
    this->setCentralWidget(mSceneView);
}

void Dungeon::nextLevel() {
    if (std::stoi(mCurrentLevel.level) == mLevelData.size()) {
        std::cout << "It's the highest level, can't move to the next level" << std::endl;
        return;
    }

    mMediaPlayer->nextLevel->play();
    int heroLife = mHero->getLife();
    mCurrentLevel = mLevelData[std::stoi(mCurrentLevel.level)];
    battle();
    mHero->setLife(heroLife);
    mHero->setFocus();
    this->setCentralWidget(mSceneView);
}

void Dungeon::battle() {
    mIntroScene->fadeOut(4000);
    mGameScene->setSceneImg(UIResource::kSceneImg);
    mHero->setHeroImg(UIResource::kHero);
    mGameScene->generatorRandomMap(UIResource::kBrickImg, mCurrentLevel);

    QTimer::singleShot(4000, [&]() {mSceneView->setScene(mGameScene);  mHero->setFocus();

    mMediaPlayer->battle->play();  });
}

void Dungeon::restart() {
    mCurrentLevel = mLevelData[0];
    mHero->setLife(3);
    menu();
}
