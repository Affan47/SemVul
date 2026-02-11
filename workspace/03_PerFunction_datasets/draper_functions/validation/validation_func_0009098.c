stopFetching()
{
    DEBUG_FUNC_INFO

    m_fetchCovers.clear();
    m_fetchingCovers = false;
    m_progress->endProgressOperation( m_fetcher );
    updateStatusBar();
}
