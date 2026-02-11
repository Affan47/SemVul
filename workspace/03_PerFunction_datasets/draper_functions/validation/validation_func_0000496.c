currentControllers() const
{
    QStringList rv = d->mControllerMap.keys();
    rv.removeOne(d->mBackgroundControllerName);

    return rv;
}
