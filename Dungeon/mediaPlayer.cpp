#include "mediaPlayer.h"

#include <QUrl>

MediaPlayer::MediaPlayer() {
    potion = new QMediaPlayer();
    potion->setMedia(QUrl::fromLocalFile("Resources\\mp3\\potion.mp3"));
    potion->setVolume(50);


    collection = new QMediaPlayer();
    collection->setMedia(QUrl::fromLocalFile("Resources\\mp3\\collection.mp3"));
    collection->setVolume(50);

    monster = new QMediaPlayer();
    monster->setMedia(QUrl::fromLocalFile("Resources\\mp3\\monster.mp3"));
    monster->setVolume(50);

    nextLevel = new QMediaPlayer();
    nextLevel->setMedia(QUrl::fromLocalFile("Resources\\mp3\\nextLevel.mp3"));
    nextLevel->setVolume(50);

    trap = new QMediaPlayer();
    trap->setMedia(QUrl::fromLocalFile("Resources\\mp3\\trap.mp3"));
    trap->setVolume(50);


    mainMenu = new QMediaPlayer();
    mainMenu->setMedia(QUrl::fromLocalFile("Resources\\mp3\\menu.mp3"));
    mainMenu->setVolume(50);

    QObject::connect(mainMenu, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            mainMenu->play();
        }
        });

    endingWin = new QMediaPlayer();
    endingWin->setMedia(QUrl::fromLocalFile("Resources\\mp3\\win.mp3"));
    endingWin->setVolume(50);

    QObject::connect(endingWin, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingWin->play();
        }
        });

    endingLose = new QMediaPlayer();
    endingLose->setMedia(QUrl::fromLocalFile("Resources\\mp3\\lose.mp3"));
    endingLose->setVolume(50);

    QObject::connect(endingLose, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingLose->play();
        }
        });


    start = new QMediaPlayer();
    start->setMedia(QUrl::fromLocalFile("Resources\\mp3\\start.mp3"));
    start->setVolume(50);

    battle = new QMediaPlayer();
    battle->setMedia(QUrl::fromLocalFile("Resources\\mp3\\battle.mp3"));
    QObject::connect(battle, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            battle->play();
        }
        });
    battle->setVolume(50);
}
