#pragma once
#include <QGraphicsPixmapItem>

class SuperPotion : public QGraphicsPixmapItem {
public:
	SuperPotion();
	void setPotionImg(const QString& kPotionImg);
	void disappear();
};
