#pragma once

#include <QObject>
#include <QGraphicsPixmapItem>
#include "hero.h"

class Dragon : public QObject, public QGraphicsPixmapItem {
	Q_OBJECT

public:
	Dragon(Hero* hero);
	virtual ~Dragon() {}

	void setDragonImg(const QString& kDragonImg);
	void keyPressEvent(QKeyEvent* event);
	void setStepSize(const int& kStepSize);
	void randomMove();

private:
	int brickSize;
	Hero* hero;
	float speedMultiplier;
	QRectF boundary;
	QGraphicsPixmapItem* exclamationMark;
};
