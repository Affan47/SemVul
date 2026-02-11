loadSettings()
{
#if QT_VERSION >= 0x040600 || defined(WEBKIT_TRUNK)
    QSettings settings;
    settings.beginGroup(QLatin1String("WebView"));
    m_enableAccessKeys = settings.value(QLatin1String("enableAccessKeys"), m_enableAccessKeys).toBool();

    if (!m_enableAccessKeys)
        hideAccessKeys();
#endif
    m_page->loadSettings();
}
