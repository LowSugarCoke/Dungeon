/**
 * @file
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief
 */

#pragma once

#include <QGraphicsView>



class GameView : public QGraphicsView {
public:
    GameView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
};
