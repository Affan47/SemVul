sourceRequestEvent(const QString &source)
{
    setData(source, Data());

    if (m_service) {
        createSource(source);
    } else {
        m_pendingSources.append(source);
    }

    return true;
}
