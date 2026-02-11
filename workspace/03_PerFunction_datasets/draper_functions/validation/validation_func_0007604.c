wait()
{
    if (!m_hThreadHandle || !m_task)
        return false;

    ACE_THR_FUNC_RETURN _value = ACE_THR_FUNC_RETURN(-1);
    int _res = ACE_Thread::join(m_hThreadHandle, &_value);

    m_iThreadId = 0;
    m_hThreadHandle = 0;

    return (_res == 0);
}
