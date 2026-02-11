timerEvent(QTimerEvent *event)
{
    Q_D(QMediaImageViewer);

    if (event->timerId() == d->timer.timerId()) {
        d->timer.stop();
        removePropertyWatch("elapsedTime");
        emit elapsedTimeChanged(d->pauseTime = d->timeout);

        d->playlist->next();

        if (d->playlist->currentIndex() < 0) {
            d->pauseTime = 0;
            emit stateChanged(d->state = StoppedState);
            emit elapsedTimeChanged(0);
        }
    } else {
        QMediaObject::timerEvent(event);
    }
}
