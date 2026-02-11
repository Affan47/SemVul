setSeekPercentage(int percentage)
{
    m_SeekTime.clear();
    m_SeekPercentage = percentage > 95 ? 95 : percentage;
}
