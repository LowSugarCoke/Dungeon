/**
 * @file mainMenuScene.h
 * @author Jack Lee
 * @date 2023.06.22
 *
 * @brief This file declares the MainMenuScene class, which represents the main menu of the game.
 */

#pragma once

#include <QGraphicsScene>
#include <QSlider>
#include <QGraphicsPixmapItem>
#include <QGraphicsOpacityEffect>
#include <QGraphicsLinearLayout>
#include <QPushButton>

class MainMenuScene : public QGraphicsScene
{
    Q_OBJECT
public:

    /**
     * @brief Constructor for the MainMenuScene class.
     * @param parent The parent QObject that owns this MainMenuScene.
     */
    MainMenuScene(QObject* parent = nullptr);

    /**
     * @brief Set the image of the main menu scene.
     * @param kSceneImg The image to set.
     */
    void setSceneImg(const QString& kSceneImg);

    /**
     * @brief Create a fade in animation over the specified duration.
     * @param duration The duration of the animation in milliseconds.
     */
    void fadeIn(int duration);

    /**
     * @brief Create a fade out animation over the specified duration.
     * @param duration The duration of the animation in milliseconds.
     */
    void fadeOut(int duration);

private:
    QGraphicsPixmapItem* mBackgroundItem;  // The background image of the scene.
    QGraphicsOpacityEffect* mOpacityEffect;  // The opacity effect used for fade in/out.

    QPushButton* mStartButton;  // The start button.
    QPushButton* mSettingsButton;  // The settings button.
    QPushButton* mLoadingButton;  // The loading button.
    QPushButton* mExitButton;  // The exit button.
    QGraphicsPixmapItem* mTitle;  // The title of the main menu.

    /**
     * @brief Set up a QPushButton with the given text, style and add it to the specified layout.
     *
     * This function creates a QPushButton, sets up its style including font, background, and color,
     * sizes it, and then adds it into a QGraphicsLinearLayout. The button is also set to be center-aligned
     * in the layout.
     *
     * @param buttonText The text that will be displayed on the button.
     * @param layout The QGraphicsLinearLayout that the button will be added to.
     * @return A pointer to the created QPushButton.
     */
    QPushButton* MainMenuScene::setupButton(const QString& buttonText, QGraphicsLinearLayout* layout);

private slots:

    /**
     * @brief Handle the event when the start button is clicked.
     */
    void handleStartButton();

    /**
     * @brief Handle the event when the loading button is clicked.
     */
    void handleLoadingButton();

    /**
     * @brief Handle the event when the settings button is clicked.
     */
    void handleSettingsButton();

    /**
     * @brief Handle the event when the exit button is clicked.
     */
    void handleExitButton();
};
