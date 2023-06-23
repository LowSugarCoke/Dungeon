/**
 * @file gameView.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief The file contains the GameView class, a customized QGraphicsView, which is used to visualize the game scene.
 */

#pragma once

#include <QGraphicsView>

class GameView : public QGraphicsView {
public:

    /**
     * @brief Constructor for the GameView class.
     *
     * @param scene A pointer to a QGraphicsScene object representing the scene to visualize.
     * @param parent An optional pointer to a QWidget object representing the parent of the GameView. Default is nullptr.
     */
    GameView(QGraphicsScene* scene, QWidget* parent = nullptr);

protected:
    /**
     * @brief Overridden from QGraphicsView. This method is called whenever the GameView is resized.
     *
     * @param event A pointer to a QResizeEvent object representing the resize event.
     */
    void resizeEvent(QResizeEvent* event) override;

    /**
     * @brief Overridden from QGraphicsView. This method is called whenever the mouse button is pressed over the GameView.
     * If the mouse press event is on a QGraphicsPixmapItem or the background, the event is ignored and the focus is not changed.
     * Otherwise, the event is passed to the parent QGraphicsView for normal processing.
     *
     * @param event A pointer to a QMouseEvent object representing the mouse press event.
     */
    void mousePressEvent(QMouseEvent* event);
};
