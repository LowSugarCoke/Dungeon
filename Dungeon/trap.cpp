// trap.cpp
#include "trap.h"

#include <QPixmap>

Trap::Trap()
    : QGraphicsPixmapItem() {}

void Trap::setTrapImg(const QString& kTrapImg) {
    QPixmap pixmap(kTrapImg);  // Change this to your image path
    setPixmap(pixmap.scaled(QSize(34, 34), Qt::KeepAspectRatio));
}

// ... other methods as needed
