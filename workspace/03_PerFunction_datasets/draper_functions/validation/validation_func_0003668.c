initHelper(const QString &name)
{
    new AuthAdaptor(this);

    if (!QDBusConnection::systemBus().registerService(name)) {
        return false;
    }

    if (!QDBusConnection::systemBus().registerObject(QLatin1String("/"), this)) {
        return false;
    }

    m_name = name;

    return true;
}
