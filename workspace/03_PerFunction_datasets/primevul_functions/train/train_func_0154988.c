QString ImportEPUB::PrepareOPFForReading(const QString &source)
{
    QString source_copy(source);
    QString prefix = source_copy.left(XML_DECLARATION_SEARCH_PREFIX_SIZE);
    QRegularExpression version(VERSION_ATTRIBUTE);
    QRegularExpressionMatch mo = version.match(prefix);
    if (mo.hasMatch()) {


        source_copy.replace(mo.capturedStart(1), mo.capturedLength(1), "1.0");
    }
    return source_copy;
}
