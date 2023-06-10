#pragma once

#include <QGraphicsView>



class GameView : public QGraphicsView {
public:
    GameView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
