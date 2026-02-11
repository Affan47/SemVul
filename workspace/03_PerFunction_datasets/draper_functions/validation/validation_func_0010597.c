timerEvent(QTimerEvent *event)
{
    if (event->timerId() != m_timerId) {
        QObject::timerEvent(event);
        return;
    }

    if (m_resetTimer) {
        killTimer(m_timerId);
        m_timerId = startTimer(m_interval);
        m_resetTimer = false;
    }

    if (m_align != Plasma::NoAlignment) {
        checkAlignment();
    }

    emit dc->updateRequested(dc);
    if (d->hasUpdates()) {

        emit dataUpdated(dc->objectName(), d->data);
        m_queued = false;
    } else {


        m_queued = true;
    }
}

}
