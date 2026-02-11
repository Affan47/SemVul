execute() {
    m_commandlist[m_state]->execute();
    if (++m_state >= m_commandlist.size())
        m_state = 0;
}
