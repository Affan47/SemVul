emitReparseSlaveConfiguration()
{


    schedulerPrivate->slotReparseSlaveConfiguration(QString(), QDBusMessage());

    schedulerPrivate->m_ignoreConfigReparse = true;
    emit self()->reparseSlaveConfiguration( QString() );
}
