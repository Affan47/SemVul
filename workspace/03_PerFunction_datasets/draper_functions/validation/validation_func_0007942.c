play(Sea::Player player, const HitInfo& info)
{
    if (m_media) {
        QString sound;
        if (info.type == HitInfo::HIT) {
            if (info.shipDestroyed) {
                sound = "ship-sink.ogg";
            }
            else {
                sound = player == Sea::PLAYER_A ?
                                "ship-player1-shoot.ogg" :
                                "ship-player2-shoot.ogg";
            }
        }
        else {
            sound = "ship-player-shoot-water.ogg";
        }

        if (!sound.isEmpty()) {
            kDebug() << "****** playing" << m_dir.filePath(sound);
            m_media->setCurrentSource(m_dir.filePath(sound));
            m_media->play();
        }
    }
}
