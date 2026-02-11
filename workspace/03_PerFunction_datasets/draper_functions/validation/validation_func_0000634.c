loadDynamicFactories(QHash<QString, QLandmarkManagerEngineFactory*> *factories)
{
    QStringList paths;
    paths << mobilityPlugins(QLatin1String("landmarks"));

    QPluginLoader qpl;
    for (int i=0;i < paths.count(); ++i) {
        qpl.setFileName(paths.at(i));

        QLandmarkManagerEngineFactory *f = qobject_cast<QLandmarkManagerEngineFactory*>(qpl.instance());
        if (f) {
            QString name = f->managerName();

#if !defined QT_NO_DEBUG
            const bool showDebug = qgetenv("QT_DEBUG_PLUGINS").toInt() > 0;
            if (showDebug)
                qDebug() << "Dynamic: found an engine plugin with name" << name;
#endif
            factories->insertMulti(name,f);
        }
    }
}
