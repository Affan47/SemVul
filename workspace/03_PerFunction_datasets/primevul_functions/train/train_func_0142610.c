QString Utility::getSpellingSafeText(const QString &raw_text)
{


    QString text(raw_text);
    return text.replace(QChar(0x2019),QChar(0x27));
}
