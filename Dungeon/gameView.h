#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>

class GameScene;
class GameView : public QGraphicsView {
public:
    GameView(GameScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
};

class GameScene : public QGraphicsScene
{
public:
    GameScene(QObject* parent = nullptr);
};
