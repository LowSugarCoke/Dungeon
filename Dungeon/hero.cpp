#include "hero.h"

#include <QObject>
#include <QKeyEvent>
#include <QTimer>

#include "monster.h"
#include "gameScene.h"
#include "collection.h"
#include "potion.h"
#include "trap.h"
#include "superPotion.h"
#include "dragon.h"

Hero::Hero()
    : QGraphicsPixmapItem()
    , mOpacityEffect(new QGraphicsOpacityEffect(this)),
    mInvincibleTimer(new QTimer(this)),
    mBlinkTimer(new QTimer(this)),
    mIsInvincible(false),
    mBlinkState(0),
    mBrickSize(40),
    mLife(3)
{
    setGraphicsEffect(mOpacityEffect);
    QObject::connect(mInvincibleTimer, &QTimer::timeout, this, &Hero::stopInvincibleMode);
    QObject::connect(mBlinkTimer, &QTimer::timeout, this, &Hero::blink);

    setFlag(QGraphicsItem::ItemIsFocusable, true);

    mIsFrozen = false;
}

void Hero::setHeroImg(const QString& kHeroImg) {
    QPixmap pixmap(kHeroImg);
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void Hero::keyPressEvent(QKeyEvent* event) {
    if (mIsFrozen) {
        return;
    }

    QPointF newPos = pos();
    QPointF beforePos = pos();
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
        newPos.setY(newPos.y() - mBrickSize);
    }
    else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
        newPos.setY(newPos.y() + mBrickSize);
    }
    else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        newPos.setX(newPos.x() - mBrickSize);
    }
    else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        newPos.setX(newPos.x() + mBrickSize);
    }
    else if (event->key() == Qt::Key_O) {
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->level = 10;
            gameScene->nextLevel();
            return;
        }
    }
    else if (event->key() == Qt::Key_P) {
        GameScene* gameScene = dynamic_cast<GameScene*>(scene());
        if (gameScene) {
            gameScene->updateLifeText(mLife);
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

    setPos(newPos);
    checkCollision();

    QList<QGraphicsItem*> collidingItems = this->collidingItems();

    if (!mIsInvincible) {
        for (auto* item : collidingItems) {
            auto* trap = dynamic_cast<Trap*>(item);
            if (trap) {
                mTrapSound->play();
                QGraphicsItem::keyPressEvent(event);
                mIsFrozen = true;
                QTimer::singleShot(1000, [this]() {
                    mIsFrozen = false;
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

    QGraphicsItem::keyPressEvent(event);
}

void Hero::setStepSize(const int& kStepSize) {
    mBrickSize = kStepSize;
}

void Hero::decreaseLife() {
    if (mLife > 0) {
        --mLife;
        QPointF newPos(mStartPos.first, mStartPos.second);
        setPos(newPos);
    }

    GameScene* gameScene = dynamic_cast<GameScene*>(scene());
    if (gameScene) {
        gameScene->updateLifeText(mLife);
    }

    if (mLife == 0) {
        if (gameScene) {
            gameScene->lose();
        }
    }
}

int Hero::getLife() const {
    return mLife;
}

void Hero::setLife(int mLife) {
    this->mLife = mLife;
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

            GameScene* gameScene = dynamic_cast<GameScene*>(scene());
            if (gameScene) {
                gameScene->updateLifeText(mLife);
            }
        }

        auto* superPotion = dynamic_cast<SuperPotion*>(item);
        if (superPotion) {
            mSuperPotionSound->play();
            superPotion->disappear();

            startInvincibleMode(10000);
        }

        if (!mIsInvincible) {
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
    mIsInvincible = true;
    mBlinkTimer->start(100);
    mInvincibleTimer->start(durationMs);
}

void Hero::stopInvincibleMode() {
    mIsInvincible = false;
    mBlinkTimer->stop();
    mOpacityEffect->setOpacity(1);
}

void Hero::blink() {
    mBlinkState = !mBlinkState;
    mOpacityEffect->setOpacity(mBlinkState);
}

void Hero::setStartPos(std::pair<int, int> mStartPos) {
    this->mStartPos = mStartPos;
}

void Hero::addLife() {
    mLife += 1;
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
