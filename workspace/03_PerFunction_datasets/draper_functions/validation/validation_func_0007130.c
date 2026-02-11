processedUrls(const QString &label, const QString &lang) const
{
    QStringList urls;
    foreach(const Engine *e, d->m_Engines) {
        if (e->lang == lang && (e->label == label || e->processedLabel_Url.keys().contains(label)))
            urls << e->processedLabel_Url.values(label);
    }
    return urls;
}
