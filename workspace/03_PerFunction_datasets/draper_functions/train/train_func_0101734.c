nodeForUrl(const KUrl& _url) const
{
    KUrl url = cleanupUrl(_url);
    if (url == urlForNode(m_rootNode))
        return m_rootNode;
    return m_nodeHash.value(url);
}
