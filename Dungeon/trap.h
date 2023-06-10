#pragma once

#include <QGraphicsPixmapItem>

class Trap : public QGraphicsPixmapItem {
public:
    Trap();

    void setTrapImg(const QString& kTrapImg);

    // ... other methods as needed

private:
    // ... private data members as needed
};
