sleep( int ms )
{
    if ( m_animTimer )
    {
        killTimer( m_animTimer );
        m_animTimer = 0;
    }
    if ( !m_sleepTimer )
        m_sleepTimer = startTimer( ms );
}
