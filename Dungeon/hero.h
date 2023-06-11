#pragma once

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QSoundEffect>


class Hero : public QGraphicsPixmapItem {
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
    void setMonsterSound(QMediaPlayer* sound);
    void setPotionSound(QMediaPlayer* sound);
    void setCollectionSound(QMediaPlayer* sound);
    void setTrapSound(QMediaPlayer* trap);

private:
    int brickSize = 40;  // Save the size of your maze cells here
    int life = 3;
    std::pair<int, int> startPos;
    bool isFrozen;
    QMediaPlayer* monsterSound;  // 新增的音效播放器
    QMediaPlayer* potionSound;
    QMediaPlayer* collectionSound;
    QMediaPlayer* trapSound;
};
