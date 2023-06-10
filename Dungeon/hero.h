#pragma once

#include <QGraphicsPixmapItem>

class Hero : public QGraphicsPixmapItem {
public:
    Hero();
    void setHeroImg(const QString& kHeroImg);
    void setStepSize(const int& kStepSize);
    void keyPressEvent(QKeyEvent* event) override;
private:
    int brickSize = 40;  // Save the size of your maze cells here
};
