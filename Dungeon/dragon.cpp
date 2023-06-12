#include "dragon.h"

#include "hero.h"
#include "collection.h"
#include "potion.h"
#include "trap.h"
#include "brickItem.h"
#include "superPotion.h"

#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QCoreApplication>

Dragon::Dragon(Hero* hero)
	: QGraphicsPixmapItem(),
	hero(hero),
	speedMultiplier(1.0f) {
	setFlag(QGraphicsItem::ItemIsFocusable, true);  // Set item to be focusable
	boundary = QRectF(140, 70, 1400, 700);
	QPixmap pixmap("Resources\\img\\exclamationMark.png");  // Change this to your image path
	exclamationMark = new QGraphicsPixmapItem(pixmap.scaled(QSize(50, 50), Qt::KeepAspectRatio), this);
	exclamationMark->setPos(pos().x() + 110, pos().y() - exclamationMark->boundingRect().height());
	exclamationMark->setVisible(false);
}

void Dragon::setDragonImg(const QString& kDragonImg) {
	QPixmap pixmap(kDragonImg);  // Change this to your image path
	setPixmap(pixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio));
}

void Dragon::keyPressEvent(QKeyEvent* event) {
	// Calculate new position
	QPointF newPos = pos();
	QPointF beforePos = pos();
	if (event->key() == Qt::Key_W) {
		newPos.setY(newPos.y() - brickSize * speedMultiplier);
	}
	else if (event->key() == Qt::Key_S) {
		newPos.setY(newPos.y() + brickSize * speedMultiplier);
	}
	else if (event->key() == Qt::Key_A) {
		newPos.setX(newPos.x() - brickSize * speedMultiplier);
	}
	else if (event->key() == Qt::Key_D) {
		newPos.setX(newPos.x() + brickSize * speedMultiplier);
	}

	// Check if the new position is within the boundary
	if (!boundary.contains(newPos)) {
		return;  // If the new position is out of boundary, do not move
	}

	// Check for collisions
	setPos(newPos);

	if (!collidingItems().isEmpty()) {
		// Check for collisions with the hero after the move
		QList<QGraphicsItem*> collidingItems = this->collidingItems();

		for (auto* item : collidingItems) {
			// Check if the colliding item is the hero
			auto* hero = dynamic_cast<Hero*>(item);
			if (hero) {
				hero->checkCollision();
				// If colliding with any item, undo move
			}
		}
	}

	QGraphicsItem::keyPressEvent(event);  // Pass the event to the base class
}

void Dragon::setStepSize(const int& kStepSize) {
	brickSize = kStepSize;
}

void Dragon::randomMove() {
	// Check if the hero is in the detection range
	qreal distanceToHero = QLineF(pos(), hero->pos()).length();
	if (distanceToHero < 300) {
		exclamationMark->setVisible(true);
		// If the hero is detected, move toward the hero

		// x-axis move
		if (pos().x() < hero->pos().x()) {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
		else {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}

		// y-axis move
		if (pos().y() < hero->pos().y()) {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
		else {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
	}
	else {
		exclamationMark->setVisible(false);
		QKeyEvent* event;
		// Random x-axis move
		if (QRandomGenerator::global()->bounded(2) == 0) {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_A, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
		else {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_D, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}

		// Random y-axis move
		if (QRandomGenerator::global()->bounded(2) == 0) {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_W, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
		else {
			QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_S, Qt::NoModifier);
			keyPressEvent(event);
			delete event;
		}
	}
}