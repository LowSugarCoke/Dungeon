#include "hero.h"

#include "monster.h"
#include "gameScene.h"
#include "collection.h"
#include "potion.h"
#include "trap.h"
#include "superPotion.h"
#include "dragon.h"

#include <QObject>

#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

#include <qdebug.h>

Hero::Hero()
	: QGraphicsPixmapItem() // 初始化音效播
	, opacityEffect(new QGraphicsOpacityEffect(this)),
	invincibleTimer(new QTimer(this)),
	blinkTimer(new QTimer(this)),
	isInvincible(false),
	blinkState(0)
{
	setGraphicsEffect(opacityEffect);
	QObject::connect(invincibleTimer, &QTimer::timeout, this, &Hero::stopInvincibleMode);
	QObject::connect(blinkTimer, &QTimer::timeout, this, &Hero::blink);

	setFlag(QGraphicsItem::ItemIsFocusable, true);  // Set item to be focusable
  // Update the life text
	isFrozen = false;
}

void Hero::setHeroImg(const QString& kHeroImg) {
	QPixmap pixmap(kHeroImg);  // Change this to your image path
	setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Hero::keyPressEvent(QKeyEvent* event) {
	if (isFrozen) {
		return;  // Ignore user input if hero is frozen
	}

	qDebug() << "Key Pressed: " << event->text();

	// Calculate new position
	QPointF newPos = pos();
	QPointF beforePos = pos();
	if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
		newPos.setY(newPos.y() - brickSize);
	}
	else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
		newPos.setY(newPos.y() + brickSize);
	}
	else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
		newPos.setX(newPos.x() - brickSize);
	}
	else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
		newPos.setX(newPos.x() + brickSize);
	}
	else if (event->key() == Qt::Key_O) {
		// Update the life text
		GameScene* gameScene = dynamic_cast<GameScene*>(scene());
		if (gameScene) {
			gameScene->level = 10;
			gameScene->nextLevel();
		}
	}
	else if (event->key() == Qt::Key_P) {
		// Update the life text
		GameScene* gameScene = dynamic_cast<GameScene*>(scene());
		if (gameScene) {
			gameScene->updateLifeText(life);
			gameScene->lose();
		}
	}

	// Check for collisions
	setPos(newPos);
	checkCollision();

	QList<QGraphicsItem*> collidingItems = this->collidingItems();

	if (!isInvincible) {
		for (auto* item : collidingItems) {
			auto* trap = dynamic_cast<Trap*>(item);
			if (trap) {
				trapSound->play();
				QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
				isFrozen = true;
				QTimer::singleShot(1000, [this]() {
					isFrozen = false;
					});
				return;
			}
		}
	}

	for (auto* item : collidingItems) {
		auto* brick = dynamic_cast<BrickItem*>(item);
		if (brick) {
			setPos(beforePos);
			return;
		}
	}

	QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}

void Hero::setStepSize(const int& kStepSize) {
	brickSize = kStepSize;
}

void Hero::decreaseLife() {
	if (life > 0) {
		--life;
		QPointF newPos(startPos.first, startPos.second);
		setPos(newPos);
	}

	// Update the life text
	GameScene* gameScene = dynamic_cast<GameScene*>(scene());
	if (gameScene) {
		gameScene->updateLifeText(life);
	}

	// if life becomes 0, restart the game or handle game over
	if (life == 0) {
		if (gameScene) {
			gameScene->lose();
		}
	}
}

int Hero::getLife() const {
	return life;
}

void Hero::setLife(int life) {
	this->life = life;
}

void Hero::checkCollision() {
	QList<QGraphicsItem*> collidingItems = this->collidingItems();

	for (auto* item : collidingItems) {
		auto* collection = dynamic_cast<Collection*>(item);
		if (collection) {
			collectionSound->play();
			collection->disappear();
		}
		auto* potion = dynamic_cast<Potion*>(item);
		if (potion) {
			potionSound->play();
			addLife();
			potion->disappear();

			// Update the life text
			GameScene* gameScene = dynamic_cast<GameScene*>(scene());
			if (gameScene) {
				gameScene->updateLifeText(life);
			}
		}

		auto* superPotion = dynamic_cast<SuperPotion*>(item);
		if (superPotion) {
			superPotionSound->play();
			superPotion->disappear();

			startInvincibleMode(10000);
		}

		if (!isInvincible) {
			auto* monster = dynamic_cast<Monster*>(item);
			if (monster) {
				monsterSound->play();
				this->decreaseLife();
			}
			auto* dragon = dynamic_cast<Dragon*>(item);
			if (dragon) {
				monsterSound->play();
				this->decreaseLife();
			}
		}
	}
}

void Hero::startInvincibleMode(int durationMs) {
	isInvincible = true;
	blinkTimer->start(100);  // 閃爍間隔，可以調整
	invincibleTimer->start(durationMs);  // 無敵模式持續時間
}

void Hero::stopInvincibleMode() {
	isInvincible = false;
	blinkTimer->stop();
	opacityEffect->setOpacity(1);  // 停止閃爍，恢復正常狀態
}

void Hero::blink() {
	blinkState = !blinkState;
	opacityEffect->setOpacity(blinkState);
}

void Hero::setStartPos(std::pair<int, int> startPos) {
	this->startPos = startPos;
}

void Hero::addLife() {
	life += 1;
}

void Hero::setMonsterSound(QMediaPlayer* sound) {
	monsterSound = sound;
}

void Hero::setDrangonSound(QMediaPlayer* sound) {
	drangonSound = sound;
}

void Hero::setPotionSound(QMediaPlayer* sound) {
	potionSound = sound;
}

void Hero::setSuperPotionSound(QMediaPlayer* sound) {
	superPotionSound = sound;
}

void Hero::setCollectionSound(QMediaPlayer* sound) {
	collectionSound = sound;
}

void Hero::setTrapSound(QMediaPlayer* trap) {
	trapSound = trap;
}