setUpdateInterval(int msec)
{
    int interval = msec;
    if (interval != 0)
        interval = qMax(msec, minimumUpdateInterval());
    QGeoPositionInfoSource::setUpdateInterval(interval);
    if (d->m_invokedStart) {
        d->stopUpdates();
        d->startUpdates();
    }
}
