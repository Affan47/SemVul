aboutToShutdown()
{
    if (Utils::Log::warnPluginsCreation())
        WARN_FUNC;


    if (m_FirstRun) {
        removeObject(m_FirstRun);
        delete m_FirstRun;
        m_FirstRun = 0;
    }
    delete _mode;
    delete _core;
    return SynchronousShutdown;
}
