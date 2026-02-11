worldTransform()
{
    if ( m_tracking != NoTracking )
        return m_transform * m_scale;
    else
        return m_scale;
}
