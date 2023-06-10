#include "gameScene.h"

#include "brickItem.h"

GameScene::GameScene(QObject* parent)
    : QGraphicsScene(parent) {

}

void GameScene::setSceneImg(const QString& kSceneImg) {
    QImage backgroundImage(kSceneImg);
    setBackgroundBrush(QBrush(backgroundImage));
}

void GameScene::generatorRandomMap(const QString& kBrickImg, Difficulty difficulty) {
    MazeGenerator maze(30, 15, difficulty);  // Create a 30x15 maze
    QImage brickImage(kBrickImg);

    // Adjust the size of the pixmap to fit your screen resolution
    int brickSize = 30;  // Adjust this to get your desired brick size
    QPixmap scaledBrickImg = QPixmap::fromImage(brickImage).scaled(brickSize, brickSize, Qt::KeepAspectRatio);

    // Calculate the offset to center the map
    int offsetX = (width() - maze.getWidth() * brickSize) / 2;
    int offsetY = (height() - maze.getHeight() * brickSize) / 2 - 50;

    for (int i = 0; i < maze.getWidth(); ++i) {
        for (int j = 0; j < maze.getHeight(); ++j) {
            if (maze(i, j) == 1) {  // If the cell is a wall, create a brick
                BrickItem* brick = new BrickItem(nullptr);
                brick->setPixmap(scaledBrickImg);
                brick->setPos(offsetX + i * brick->pixmap().width(), offsetY + j * brick->pixmap().height());
                this->addItem(brick);
            }
        }
    }
}
