#include "mediaPlayer.h"

#include <QUrl>

#include "resource.h"

MediaPlayer::MediaPlayer() {
    potion = new QMediaPlayer();
    potion->setMedia(QUrl::fromLocalFile(MusicResource::kPotion));
    potion->setVolume(50);

    superPotion = new QMediaPlayer();
    superPotion->setMedia(QUrl::fromLocalFile(MusicResource::kSuperPotion));
    superPotion->setVolume(50);

    collection = new QMediaPlayer();
    collection->setMedia(QUrl::fromLocalFile(MusicResource::kCollection));
    collection->setVolume(50);

    monster = new QMediaPlayer();
    monster->setMedia(QUrl::fromLocalFile(MusicResource::kMonster));
    monster->setVolume(50);

    nextLevel = new QMediaPlayer();
    nextLevel->setMedia(QUrl::fromLocalFile(MusicResource::kNextLevel));
    nextLevel->setVolume(50);

    trap = new QMediaPlayer();
    trap->setMedia(QUrl::fromLocalFile(MusicResource::kTrap));
    trap->setVolume(50);

    mainMenu = new QMediaPlayer();
    mainMenu->setMedia(QUrl::fromLocalFile(MusicResource::kMainMenu));
    mainMenu->setVolume(50);

    QObject::connect(mainMenu, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            mainMenu->play();
        }
        });

    endingWin = new QMediaPlayer();
    endingWin->setMedia(QUrl::fromLocalFile(MusicResource::kEndingWin));
    endingWin->setVolume(50);

    QObject::connect(endingWin, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingWin->play();
        }
        });

    endingLose = new QMediaPlayer();
    endingLose->setMedia(QUrl::fromLocalFile(MusicResource::kEndingLose));
    endingLose->setVolume(50);

    QObject::connect(endingLose, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingLose->play();
        }
        });

    start = new QMediaPlayer();
    start->setMedia(QUrl::fromLocalFile(MusicResource::kDragon));
    start->setVolume(50);

    battle = new QMediaPlayer();
    battle->setMedia(QUrl::fromLocalFile(MusicResource::kBattle));
    QObject::connect(battle, &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            battle->play();
        }
        });
    battle->setVolume(50);
}
