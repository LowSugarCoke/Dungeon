#include "settingScene.h"


#include <QSlider>
#include <QGraphicsProxyWidget>

#include "Dungeon.h"

SettingScene::SettingScene(MediaPlayer* player, QObject* parent)
    : QGraphicsScene(parent),
    mediaPlayer(player)
{
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(70);
    volumeSlider->setStyleSheet(R"(
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



    QGraphicsProxyWidget* volumeSliderProxy = addWidget(volumeSlider);
    volumeSliderProxy->setPos(700, 300);
    volumeSliderProxy->resize(400, 120); // Change this line to resize the slider to match the buttons

    connect(volumeSlider, &QSlider::valueChanged, this, &SettingScene::adjustVolume);


    backButton = new QPushButton(QString::fromLocal8Bit("返回主菜單"));
    backButton->setMinimumSize(400, 120);
    backButton->setMaximumSize(400, 120);
    backButton->setStyleSheet(R"(
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
    QGraphicsProxyWidget* backButtonProxy = addWidget(backButton);
    backButtonProxy->setPos(700, 500);  // 调整位置
    connect(backButton, &QPushButton::clicked, this, &SettingScene::handleBackButton);
}

void SettingScene::adjustVolume(int volume) {
    // 使用QMediaPlayer的setVolume方法调整所有音频的音量
    mediaPlayer->potion->setVolume(volume);
    mediaPlayer->collection->setVolume(volume);
    mediaPlayer->monster->setVolume(volume);
    mediaPlayer->nextLevel->setVolume(volume);
    mediaPlayer->trap->setVolume(volume);
    mediaPlayer->mainMenu->setVolume(volume);
    mediaPlayer->start->setVolume(volume);
    mediaPlayer->battle->setVolume(volume);
    mediaPlayer->endingWin->setVolume(volume);
    mediaPlayer->endingLose->setVolume(volume);
}

void SettingScene::setSceneImg(const QString& kSceneImg) {
    QPixmap backgroundImage(kSceneImg);
    backgroundImage = backgroundImage.scaled(this->width(), this->height(), Qt::KeepAspectRatioByExpanding);
    setBackgroundBrush(backgroundImage);
}

void SettingScene::handleBackButton() {
    static_cast<Dungeon*>(parent())->menu();
}
