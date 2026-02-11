openLastTab()
{
    if (m_recentlyClosedTabs.isEmpty())
        return;
    QUrl url = m_recentlyClosedTabs.takeFirst();
    QByteArray historyState = m_recentlyClosedTabsHistory.takeFirst();
#if QT_VERSION >= 0x040600
    createTab(historyState, NewTab);
#else
    loadUrl(url, NewTab);
#endif
    m_recentlyClosedTabsAction->setEnabled(!m_recentlyClosedTabs.isEmpty());
}
