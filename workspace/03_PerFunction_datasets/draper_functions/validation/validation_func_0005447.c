distinctIds() const
{
    if ( m_subtypes.isEmpty() )
        return QList<int>() << m_baseId;
    else
        return m_subtypes.keys();
}
