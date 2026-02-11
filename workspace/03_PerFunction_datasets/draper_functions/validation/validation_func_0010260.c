takeSlaveForJob(SimpleJob *job)
{
    Slave *slave = heldSlaveForJob(job);
    if (slave) {
        return slave;
    }

    KUrl url = SimpleJobPrivate::get(job)->m_url;

    QMultiHash<QString, Slave *>::Iterator it = m_idleSlaves.find(url.host());
    if (it == m_idleSlaves.end()) {
        it = m_idleSlaves.begin();
    }
    if (it == m_idleSlaves.end()) {
        return 0;
    }
    slave = it.value();
    m_idleSlaves.erase(it);
    return slave;
}
