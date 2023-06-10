#include <QObject>
#include <QGraphicsPixmapItem>

class Monster : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Monster();
    virtual ~Monster() {}

    void setMonsterImg(const QString& kMonsterImg);
    void keyPressEvent(QKeyEvent* event);
    void setStepSize(const int& kStepSize);
    void randomMove();

private:
    int brickSize;
};
