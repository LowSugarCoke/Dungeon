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
            return;
        }
    }
    else if (event->key() == Qt::Key_P) {
        // Update the life text
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->updateLifeText(life);
            gameScene->lose();
            return;
        }
    }
    else if (event->key() == Qt::Key_U) {
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->saveData();
            return;
        }
    }
    else if (event->key() == Qt::Key_I) {
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->callLoad();
            return;
        }
    }
    else if (event->key() == Qt::Key_Y) {
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->nextLevel();
            return;
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
                mTrapSound->play();
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
            mCollectionSound->play();
            collection->disappear();
        }
        auto* potion = dynamic_cast<Potion*>(item);
        if (potion) {
            mPotionSound->play();
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
            mSuperPotionSound->play();
            superPotion->disappear();

            startInvincibleMode(10000);
        }

        if (!isInvincible) {
            auto* monster = dynamic_cast<Monster*>(item);
            if (monster) {
                mMonsterSound->play();
                this->decreaseLife();
                startInvincibleMode(2000);
            }
            auto* dragon = dynamic_cast<Dragon*>(item);
            if (dragon) {
                mMonsterSound->play();
                this->decreaseLife();
                startInvincibleMode(2000);
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

void Hero::setMonsterSound(std::shared_ptr<QMediaPlayer> monsterSound) {
    mMonsterSound = monsterSound;
}

void Hero::setDrangonSound(std::shared_ptr<QMediaPlayer> drangonSound) {
    mDrangonSound = drangonSound;
}

void Hero::setPotionSound(std::shared_ptr<QMediaPlayer> potionSound) {
    mPotionSound = potionSound;
}

void Hero::setSuperPotionSound(std::shared_ptr<QMediaPlayer> superPotionSound) {
    mSuperPotionSound = superPotionSound;
}

void Hero::setCollectionSound(std::shared_ptr<QMediaPlayer> collectionSound) {
    mCollectionSound = collectionSound;
}

void Hero::setTrapSound(std::shared_ptr<QMediaPlayer> trapSound) {
    mTrapSound = trapSound;
}
