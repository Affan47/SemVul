setPreviewState(const QString &state)
{
    QString actualState = state;
    if (actualState == QLatin1String("poster")) {
        actualState.append(" overlapped");
    }
    m_paintCanvas->setState(actualState);
}
