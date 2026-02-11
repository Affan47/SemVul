exitLoop()
{
    if (m_activeSessionCtxs.isEmpty())
        leaveModality();
    m_activeEventLoops.top()->quit();
}
