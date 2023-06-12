#include "Dungeon.h"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <QScreen>
#include <QMouseEvent>
#include <QTimer>

#include "resource.h"
#include "gameScene.h"
#include "gameView.h"
#include "collection.h"
#include "level.h"
#include "history.h"

Dungeon::Dungeon(QWidget* parent)
	: QMainWindow(parent)
	, currentLevel(Level::kLevel1)
	, hero(new Hero())
	// Initialize the hero
{
	ui.setupUi(this);

	setWindowIcon(QIcon("Resources/img/logo.png"));

	mediaPlayer = new MediaPlayer();
	hero->setPotionSound(mediaPlayer->potion);
	hero->setMonsterSound(mediaPlayer->monster);
	hero->setCollectionSound(mediaPlayer->collection);
	hero->setTrapSound(mediaPlayer->trap);
	hero->setSuperPotionSound(mediaPlayer->superPotion);
	hero->setDrangonSound(mediaPlayer->start);

	scene = new GameScene(this);

	sceneView = new GameView(scene, this);

	endingScene = new EndingScene(this);
	settingScene = new SettingScene(mediaPlayer, this);
	introScene = new IntroScene(this);

	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());
	settingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	settingScene->setSceneImg(UIResource::kMenu);

	menuScene = new MainMenuScene(this);
	menuScene->setMedia(mediaPlayer);

	introScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	introScene->setSceneImg(UIResource::kMenu);
	introScene->setMedia(mediaPlayer);

	menu();
}

void Dungeon::load() {
	mediaPlayer->mainMenu->stop();
	mediaPlayer->battle->stop();
	std::string filename = "data.txt";
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "Unable to open file: " << filename << std::endl;
		return;
	}

	History history;
	// Load maze
	for (int i = 0; i < 21; i++) {
		std::string line;
		std::getline(file, line);
		std::stringstream ss(line);

		history.maze.push_back(std::vector<int>());
		std::string cell;
		while (std::getline(ss, cell, ',')) { // Use ',' as delimiter
			history.maze.back().push_back(std::stoi(cell));
		}
	}

	// Load entities
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream is(line);
		std::string entity;
		is >> entity;
		if (entity == "Level") {
			is >> history.level;
		}
		else if (entity == "Hero") {
			is >> history.heroPos.first >> history.heroPos.second >> history.heroLife;
		}
		else if (entity == "Monster") {
			int x, y;
			while (is >> x >> y) {
				history.monsterPos.push_back({ x, y });
			}
		}
		else if (entity == "MonsterSpeed") {
			is >> history.monsterSpeed;
		}
		else if (entity == "Dragon") {
			int x, y;
			while (is >> x >> y) {
				history.dragonPos.push_back({ x, y });
			}
		}
		else if (entity == "DragonSpeed") {
			is >> history.dragonSpeed;
		}
		else if (entity == "Collection") {
			int x, y;
			while (is >> x >> y) {
				history.collectionPos.push_back({ x, y });
			}
		}
		else if (entity == "Potion") {
			int x, y;
			while (is >> x >> y) {
				history.potionPos.push_back({ x, y });
			}
		}
		else if (entity == "SuperPotion") {
			int x, y;
			while (is >> x >> y) {
				history.superPotionPos.push_back({ x, y });
			}
		}
		else if (entity == "Trap") {
			int x, y;
			while (is >> x >> y) {
				history.trapPos.push_back({ x, y });
			}
		}
	}

	file.close();

	if (history.level == 1) {
		currentLevel = Level::kLevel1;
	}
	else if (history.level == 2) {
		currentLevel = Level::kLevel2;
	}
	else if (history.level == 3) {
		currentLevel = Level::kLevel3;
	}
	else if (history.level == 4) {
		currentLevel = Level::kLevel4;
	}
	else if (history.level == 5) {
		currentLevel = Level::kLevel5;
	}
	else if (history.level == 6) {
		currentLevel = Level::kLevel6;
	}
	else if (history.level == 7) {
		currentLevel = Level::kLevel7;
	}
	else if (history.level == 8) {
		currentLevel = Level::kLevel8;
	}
	else if (history.level == 9) {
		currentLevel = Level::kLevel9;
	}
	else if (history.level == 10) {
		currentLevel = Level::kLevel10;
	}

	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());

	scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	scene->setSceneImg(UIResource::kSceneImg);
	scene->setHero(hero);
	hero->setHeroImg(UIResource::kHero);

	scene->loadData(history);
	sceneView->setScene(scene);
	hero->setFocus();
	mediaPlayer->battle->play();
}

void Dungeon::intro() {
	introScene->fadeIn(0);
	sceneView->setScene(introScene);
	introScene->startStory();
	this->setCentralWidget(sceneView);
}

void Dungeon::setting() {
	sceneView->setScene(settingScene);
}

void Dungeon::menu() {
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());
	menuScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	menuScene->setSceneImg(UIResource::kMenu);

	menuScene->fadeIn(0);
	mediaPlayer->endingWin->stop();
	mediaPlayer->endingLose->stop();
	mediaPlayer->mainMenu->play();
	sceneView->setScene(menuScene);
	this->setCentralWidget(sceneView);
}

void Dungeon::win() {
	mediaPlayer->battle->stop();
	mediaPlayer->endingWin->play();
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());
	endingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	endingScene->setSceneImg(UIResource::kWin);
	sceneView->setScene(endingScene);
	endingScene->fadeIn(1000);
	endingScene->setMessage("You Win");
	this->setCentralWidget(sceneView);
}

void Dungeon::lose() {
	mediaPlayer->battle->stop();
	mediaPlayer->endingLose->play();
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());
	endingScene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	endingScene->setSceneImg(UIResource::kLose);
	sceneView->setScene(endingScene);
	endingScene->fadeIn(1000);
	endingScene->setMessage("You Lose");
	this->setCentralWidget(sceneView);
}

void Dungeon::nextLevel() {
	mediaPlayer->nextLevel->play();

	int heroLife = hero->getLife();

	// Continue to the next level
	if (currentLevel.level == Level::kLevel1.level) {
		currentLevel = Level::kLevel2;
	}
	else if (currentLevel.level == Level::kLevel2.level) {
		currentLevel = Level::kLevel3;
	}
	else if (currentLevel.level == Level::kLevel3.level) {
		currentLevel = Level::kLevel4;
	}
	else if (currentLevel.level == Level::kLevel4.level) {
		currentLevel = Level::kLevel5;
	}
	else if (currentLevel.level == Level::kLevel5.level) {
		currentLevel = Level::kLevel6;
	}
	else if (currentLevel.level == Level::kLevel6.level) {
		currentLevel = Level::kLevel7;
	}
	else if (currentLevel.level == Level::kLevel7.level) {
		currentLevel = Level::kLevel8;
	}
	else if (currentLevel.level == Level::kLevel8.level) {
		currentLevel = Level::kLevel9;
	}
	else if (currentLevel.level == Level::kLevel9.level) {
		currentLevel = Level::kLevel10;
	}

	// Recreate the game scene for the new level
	battle();
	// Restore the Hero's life and position in the new scene
	hero->setLife(heroLife);

	hero->setFocus();
	this->setCentralWidget(sceneView);
}

void Dungeon::battle() {
	introScene->fadeOut(4000);

	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	this->resize(screenGeometry.width(), screenGeometry.height());

	scene->setSceneRect(0, 0, screenGeometry.width(), screenGeometry.height());
	scene->setSceneImg(UIResource::kSceneImg);
	hero->setHeroImg(UIResource::kHero);
	scene->setHero(hero);

	scene->generatorRandomMap(UIResource::kBrickImg, currentLevel);

	QTimer::singleShot(4000, [&]() {sceneView->setScene(scene);  hero->setFocus();
	mediaPlayer->battle->play();  });
}

void Dungeon::restart() {
	currentLevel = Level::kLevel1;
	hero->setLife(3);
	menu();
}