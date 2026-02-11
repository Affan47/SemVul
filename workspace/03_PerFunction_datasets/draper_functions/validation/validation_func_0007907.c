setMaximumHeight(qreal maximumHeight)
{
    if (maximumHeight != m_maximumHeight)
    {
        m_maximumHeight = maximumHeight;
        emit maximumHeightChanged();
        updateLayout();
    }
}
