// collection.cpp
#include "superPotion.h"

#include <QPixmap>

SuperPotion::SuperPotion()
	: QGraphicsPixmapItem() {}

void SuperPotion::setPotionImg(const QString& kPotionImg) {
	QPixmap pixmap(kPotionImg);  // Change this to your image path
	setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

void SuperPotion::disappear() {
	this->hide();
}