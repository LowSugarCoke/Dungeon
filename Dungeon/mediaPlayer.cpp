#include "mediaPlayer.h"

#include <QUrl>

#include "resource.h"

MediaPlayer::MediaPlayer() {
    potion = std::make_shared<QMediaPlayer>();
    potion->setMedia(QUrl::fromLocalFile(MusicResource::kPotion));
    potion->setVolume(50);

    superPotion = std::make_shared<QMediaPlayer>();
    superPotion->setMedia(QUrl::fromLocalFile(MusicResource::kSuperPotion));
    superPotion->setVolume(50);

    collection = std::make_shared<QMediaPlayer>();
    collection->setMedia(QUrl::fromLocalFile(MusicResource::kCollection));
    collection->setVolume(50);

    monster = std::make_shared<QMediaPlayer>();
    monster->setMedia(QUrl::fromLocalFile(MusicResource::kMonster));
    monster->setVolume(50);

    nextLevel = std::make_shared<QMediaPlayer>();
    nextLevel->setMedia(QUrl::fromLocalFile(MusicResource::kNextLevel));
    nextLevel->setVolume(50);

    trap = std::make_shared<QMediaPlayer>();
    trap->setMedia(QUrl::fromLocalFile(MusicResource::kTrap));
    trap->setVolume(50);

    mainMenu = std::make_shared<QMediaPlayer>();
    mainMenu->setMedia(QUrl::fromLocalFile(MusicResource::kMainMenu));
    mainMenu->setVolume(50);

    QObject::connect(mainMenu.get(), &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            mainMenu->play();
        }
        });

    endingWin = std::make_shared<QMediaPlayer>();
    endingWin->setMedia(QUrl::fromLocalFile(MusicResource::kEndingWin));
    endingWin->setVolume(50);

    QObject::connect(endingWin.get(), &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingWin->play();
        }
        });

    endingLose = std::make_shared<QMediaPlayer>();
    endingLose->setMedia(QUrl::fromLocalFile(MusicResource::kEndingLose));
    endingLose->setVolume(50);

    QObject::connect(endingLose.get(), &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            endingLose->play();
        }
        });

    start = std::make_shared<QMediaPlayer>();
    start->setMedia(QUrl::fromLocalFile(MusicResource::kDragon));
    start->setVolume(50);

    battle = std::make_shared<QMediaPlayer>();
    battle->setMedia(QUrl::fromLocalFile(MusicResource::kBattle));
    QObject::connect(battle.get(), &QMediaPlayer::mediaStatusChanged, [&](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            battle->play();
        }
        });
    battle->setVolume(50);
}
