#include "settingScene.h"

#include <QGraphicsProxyWidget>

#include "Dungeon.h"

SettingScene::SettingScene(std::shared_ptr<MediaPlayer> mediaPlayer, QObject* parent)
    : QGraphicsScene(parent),
    mMediaPlayer(mediaPlayer)
{
    mTextItem = new QGraphicsTextItem();
    QFont font;
    font.setPixelSize(100);
    mTextItem->setFont(font);
    mTextItem->setDefaultTextColor(QColor(255, 255, 255));
    mTextItem->setPlainText("Voice");
    mTextItem->setPos(550, 300);

    addItem(mTextItem);

    mVolumeSlider = new QSlider(Qt::Horizontal);
    mVolumeSlider->setRange(0, 100);
    mVolumeSlider->setValue(70);
    mVolumeSlider->setStyleSheet(R"(
    QSlider{
        background:transparent;
    }

    QSlider::groove:horizontal { 
        
        border: 1px solid black; 
        height: 10px; 
        background: transparent;  // 將背景設定為透明
    }
    QSlider::handle:horizontal { 
       
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); 
        border: 1px solid black; 
        width: 30px;  // 增大 handle 的寬度
        margin: -2px 0; 
        border-radius: 3px; 
    }
  QSlider::add-page:horizontal {     // 设置滑动条右侧部分（大于滑块当前值的部分）为黑色
        background: black;
    }
    QSlider::sub-page:horizontal {     // 设置滑动条左侧部分（小于滑块当前值的部分）为黑色
        background: black;
    }
)");


    QGraphicsProxyWidget* volumeSliderProxy = addWidget(mVolumeSlider);
    volumeSliderProxy->setPos(850, 300);
    volumeSliderProxy->resize(400, 120);

    connect(mVolumeSlider, &QSlider::valueChanged, this, &SettingScene::adjustVolume);


    mBackButton = new QPushButton(QString::fromLocal8Bit("返回主菜單"));
    mBackButton->setMinimumSize(400, 120);
    mBackButton->setMaximumSize(400, 120);
    mBackButton->setStyleSheet(R"(
    QPushButton { 
        font-size:20px; 
        font-weight:bold; 
        background:none; 
        background-color:transparent; 
        border-image: url(Resources/img/button.png) 0 0 0 0 stretch stretch; 
    }
    QPushButton:hover { 
        color:white;
    }
    QPushButton:pressed { 
        color:black;
    }
)");
    QGraphicsProxyWidget* backButtonProxy = addWidget(mBackButton);
    backButtonProxy->setPos(700, 500);
    connect(mBackButton, &QPushButton::clicked, this, &SettingScene::handleBackButton);
}

void SettingScene::adjustVolume(int volume) {
    mMediaPlayer->potion->setVolume(volume);
    mMediaPlayer->collection->setVolume(volume);
    mMediaPlayer->monster->setVolume(volume);
    mMediaPlayer->nextLevel->setVolume(volume);
    mMediaPlayer->trap->setVolume(volume);
    mMediaPlayer->mainMenu->setVolume(volume);
    mMediaPlayer->start->setVolume(volume);
    mMediaPlayer->battle->setVolume(volume);
    mMediaPlayer->endingWin->setVolume(volume);
    mMediaPlayer->endingLose->setVolume(volume);
}

void SettingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding);
    setBackgroundBrush(backgroundImage);
}

void SettingScene::handleBackButton() {
    static_cast<Dungeon*>(parent())->menu();
}
