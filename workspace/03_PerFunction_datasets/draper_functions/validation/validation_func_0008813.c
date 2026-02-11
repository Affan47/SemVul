grimReaper()
{
    QMultiHash<QString, Slave *>::Iterator it = m_idleSlaves.begin();
    while (it != m_idleSlaves.end()) {
        Slave *slave = it.value();
        if (slave->idleTime() >= s_idleSlaveLifetime) {
            it = m_idleSlaves.erase(it);
            if (slave->job()) {
                kDebug (7006) << "Idle slave" << slave << "still has job" << slave->job();
            }
            slave->kill();

            slave->deref();
        } else {
            ++it;
        }
    }
    if (!m_idleSlaves.isEmpty()) {
        scheduleGrimReaper();
    }
}
