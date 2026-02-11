remoteDataEngine(const KUrl &location, const QString &name)
{
    QPair<QString, QString> pair(location.prettyUrl(), name);
    kDebug() << "pair = " << pair;
    if (m_remoteEngines.contains(pair)) {
        kDebug() << "existing remote dataengine at " << location;
        return m_remoteEngines[pair];
    }

    kDebug() << "new remote dataengine at " << location;
    RemoteDataEngine *engine = new RemoteDataEngine(KUrl());
    m_remoteEngines[pair] = engine;
    Service *plasmoidService = Service::access(location);
    plasmoidService->setDestination(location.prettyUrl());
    m_engineNameForService[plasmoidService] = name;
    kDebug() << "name = " << name;
    QObject::connect(plasmoidService, SIGNAL(serviceReady(Plasma::Service*)),
                     m_monitor, SLOT(slotServiceReady(Plasma::Service*)));
    return engine;
}
