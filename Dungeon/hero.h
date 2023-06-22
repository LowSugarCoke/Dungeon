#pragma once

#include <memory>

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QObject>

class Hero :public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:

    Hero();
    void setHeroImg(const QString& kHeroImg);
    void setStepSize(const int& kStepSize);
    void keyPressEvent(QKeyEvent* event) override;
    void decreaseLife();
    void addLife();
    int getLife() const;
    void setLife(int life);
    void checkCollision();
    void setStartPos(std::pair<int, int> startPos);
    void setMonsterSound(std::shared_ptr<QMediaPlayer> monsterSound);
    void setDrangonSound(std::shared_ptr<QMediaPlayer> dragonSound);
    void setPotionSound(std::shared_ptr<QMediaPlayer> potionSound);
    void setSuperPotionSound(std::shared_ptr<QMediaPlayer> superPotionSound);
    void setCollectionSound(std::shared_ptr<QMediaPlayer> collectionSsound);
    void setTrapSound(std::shared_ptr<QMediaPlayer> trapSound);
    void startInvincibleMode(int durationMs);

private:
    int brickSize = 40;  // Save the size of your maze cells here
    int life = 3;
    std::pair<int, int> startPos;
    bool isFrozen;
    std::shared_ptr<QMediaPlayer> mMonsterSound;  // 新增的音效播放器
    std::shared_ptr<QMediaPlayer> mDrangonSound;
    std::shared_ptr<QMediaPlayer> mPotionSound;
    std::shared_ptr<QMediaPlayer> mSuperPotionSound;
    std::shared_ptr<QMediaPlayer> mCollectionSound;
    std::shared_ptr<QMediaPlayer> mTrapSound;

    QGraphicsPixmapItem* pixmapItem;
    QGraphicsOpacityEffect* opacityEffect;
    QTimer* invincibleTimer;
    QTimer* blinkTimer;
    bool isInvincible;
    int blinkState;

    void stopInvincibleMode();
    void blink();
};
