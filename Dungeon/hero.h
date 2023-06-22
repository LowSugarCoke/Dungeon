/**
 * @file
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file declares the Hero class, representing the main character of the game.
 */

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

    /**
     * @brief Constructor for the Hero class.
     */
    Hero();

    /**
     * @brief Set the image of the hero.
     * @param kHeroImg The image to set.
     */
    void setHeroImg(const QString& kHeroImg);

    /**
     * @brief Set the step size for the hero's movement.
     * @param kStepSize The step size to set.
     */
    void setStepSize(const int& kStepSize);

    /**
     * @brief Overridden from QGraphicsItem. Handles key press events for the hero.
     * @param event The event to handle.
     */
    void keyPressEvent(QKeyEvent* event) override;

    /**
     * @brief Decrease the life of the hero by one.
     */
    void decreaseLife();

    /**
     * @brief Increase the life of the hero by one.
     */
    void addLife();

    /**
     * @brief Get the current life of the hero.
     * @return The life of the hero.
     */
    int getLife() const;

    /**
     * @brief Set the life of the hero.
     * @param mLife The life to set.
     */
    void setLife(int mLife);

    /**
     * @brief Check if the hero has collided with any other game objects.
     */
    void checkCollision();

    /**
     * @brief Set the starting position of the hero.
     * @param mStartPos The starting position to set.
     */
    void setStartPos(std::pair<int, int> mStartPos);

    /**
     * @brief Set the sound to play when the hero encounters a monster.
     * @param monsterSound The sound to set.
     */
    void setMonsterSound(std::shared_ptr<QMediaPlayer> monsterSound);

    /**
     * @brief Set the sound to play when the hero encounters a dragon.
     * @param dragonSound The sound to set.
     */
    void setDrangonSound(std::shared_ptr<QMediaPlayer> dragonSound);

    /**
     * @brief Set the sound to play when the hero encounters a potion.
     * @param potionSound The sound to set.
     */
    void setPotionSound(std::shared_ptr<QMediaPlayer> potionSound);

    /**
     * @brief Set the sound to play when the hero encounters a super potion.
     * @param superPotionSound The sound to set.
     */
    void setSuperPotionSound(std::shared_ptr<QMediaPlayer> superPotionSound);

    /**
     * @brief Set the sound to play when the hero encounters a collectible item.
     * @param collectionSsound The sound to set.
     */
    void setCollectionSound(std::shared_ptr<QMediaPlayer> collectionSsound);

    /**
     * @brief Set the sound to play when the hero encounters a trap.
     * @param trapSound The sound to set.
     */
    void setTrapSound(std::shared_ptr<QMediaPlayer> trapSound);

    /**
     * @brief Start the hero's invincible mode for a specified duration.
     * @param durationMs The duration of the invincible mode in milliseconds.
     */
    void startInvincibleMode(int durationMs);

private:
    int mBrickSize;  // The size of the bricks in the game world.
    int mLife;  // The life of the hero.
    std::pair<int, int> mStartPos;  // The starting position of the hero.
    bool mIsFrozen;  // Whether the hero is frozen.
    std::shared_ptr<QMediaPlayer> mMonsterSound;  // The sound to play when the hero encounters a monster.
    std::shared_ptr<QMediaPlayer> mDrangonSound;  // The sound to play when the hero encounters a dragon.
    std::shared_ptr<QMediaPlayer> mPotionSound;  // The sound to play when the hero encounters a potion.
    std::shared_ptr<QMediaPlayer> mSuperPotionSound;  // The sound to play when the hero encounters a super potion.
    std::shared_ptr<QMediaPlayer> mCollectionSound;  // The sound to play when the hero encounters a collectible item.
    std::shared_ptr<QMediaPlayer> mTrapSound;  // The sound to play when the hero encounters a trap.

    QGraphicsOpacityEffect* mOpacityEffect;  // The effect to apply when the hero becomes invincible.
    QTimer* mInvincibleTimer;  // The timer for the hero's invincible mode.
    QTimer* mBlinkTimer;  // The timer for the hero's blinking animation when invincible.
    bool mIsInvincible;  // Whether the hero is invincible.
    int mBlinkState;  // The current state of the hero's blinking animation.

    /**
     * @brief Stop the hero's invincible mode.
     */
    void stopInvincibleMode();

    /**
     * @brief Make the hero blink during invincible mode.
     */
    void blink();
};
