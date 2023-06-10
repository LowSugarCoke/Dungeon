#pragma once
#include <QGraphicsPixmapItem>

class Collection : public QGraphicsPixmapItem {

public:
    Collection();
    void setCollectionImg(const QString& kCollectionImg);
    void disappear();

};
