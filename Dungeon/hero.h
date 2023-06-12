#pragma once

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
	void setMonsterSound(QMediaPlayer* sound);
	void setPotionSound(QMediaPlayer* sound);
	void setSuperPotionSound(QMediaPlayer* sound);
	void setCollectionSound(QMediaPlayer* sound);
	void setTrapSound(QMediaPlayer* trap);

private:
	int brickSize = 40;  // Save the size of your maze cells here
	int life = 3;
	std::pair<int, int> startPos;
	bool isFrozen;
	QMediaPlayer* monsterSound;  // 新增的音效播放器
	QMediaPlayer* potionSound;
	QMediaPlayer* superPotionSound;
	QMediaPlayer* collectionSound;
	QMediaPlayer* trapSound;

	QGraphicsPixmapItem* pixmapItem;
	QGraphicsOpacityEffect* opacityEffect;
	QTimer* invincibleTimer;
	QTimer* blinkTimer;
	bool isInvincible;
	int blinkState;

	void startInvincibleMode(int durationMs);
	void stopInvincibleMode();
	void blink();
};
