_q_stateChanged(QMediaPlayer::State ps)
{
    Q_Q(QMediaPlayer);

    if (filterStates)
        return;

    if (playlist
            && ps != state && ps == QMediaPlayer::StoppedState
            && (control->mediaStatus() == QMediaPlayer::EndOfMedia ||
                control->mediaStatus() == QMediaPlayer::InvalidMedia)) {
        playlist->next();
        ps = control->state();
    }

    if (ps != state) {
        state = ps;

        if (ps == QMediaPlayer::PlayingState)
            q->addPropertyWatch("position");
        else
            q->removePropertyWatch("position");

        emit q->stateChanged(ps);
    }
}
