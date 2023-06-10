#pragma once

#include <QGraphicsPixmapItem>

class Hero : public QGraphicsPixmapItem {
public:
    Hero();
    void setHeroImg(const QString& kHeroImg);
    void setStepSize(const int& kStepSize);
    void keyPressEvent(QKeyEvent* event) override;
    void decreaseLife();
    int getLife() const;
    void checkCollision();
    void setStartPos(std::pair<int, int> startPos);

private:
    int brickSize = 40;  // Save the size of your maze cells here
    int life = 3;
    std::pair<int, int> startPos;
};
