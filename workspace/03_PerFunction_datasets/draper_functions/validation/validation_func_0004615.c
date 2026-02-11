serializedContent() const
{
    QString tmp;
    const QStringList &schemes = Trans::ConstantTranslations::dailySchemeXmlTagList();
    foreach(int k, d->m_DailySchemes.keys()) {
        if (d->m_DailySchemes.value(k))
            tmp += "<" + schemes.at(k) + " value=" + QString::number(d->m_DailySchemes.value(k)) + "/>";
    }
    if (d->m_Method == Repeat) {
        tmp.prepend("<Repeat/>");
    } else {
        tmp.prepend("<Distribute/>");
    }
    return tmp;
}
