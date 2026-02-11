setProgress(int progress)
{
    m_progress = progress > 100 ? 100 :
        progress < 0 ? 0 :
        progress;
}
