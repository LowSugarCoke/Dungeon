#pragma once
#include <QGraphicsPixmapItem>

class Potion : public QGraphicsPixmapItem {
public:
    Potion();
    void setPotionImg(const QString& kPotionImg);
    void disappear();

};
