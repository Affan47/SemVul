eventFilter(QObject *obj, QEvent *event)
{
    if (obj == d->m_widget ) {
        switch (event->type()) {
        case QEvent::Paint:

            obj->removeEventFilter(this);
            QCoreApplication::sendEvent(obj, event);
            d->paintFrame();
            obj->installEventFilter(this);
            return true;
        break;
        case QEvent::Hide:
            d->m_timer.stop();
        break;
        case QEvent::Show:
            if(d->m_started) {
                d->m_timer.start();
                d->m_widget->update(d->pixmapRect());
            }
        break;
        default:
        break;
        }
    }

    return false;
}
