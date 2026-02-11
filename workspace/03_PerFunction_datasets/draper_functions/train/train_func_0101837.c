sessionMetaData(const QString &key) const
{
    QString value;

    KIO::Integration::AccessManager *manager = qobject_cast<KIO::Integration::AccessManager *>(networkAccessManager());
    if (manager)
        value = manager->sessionMetaData().value(key);

    return value;
}
