fromXml(const QString &xml)
{

    QDomDocument doc;
    int line = 0;
    int col = 0;
    QString error;
    if (!doc.setContent(xml, &error, &line, &col)) {
        LOG_ERROR_FOR("AlertValidation", tkTr(Trans::Constants::ERROR_1_LINE_2_COLUMN_3)
                      .arg(error).arg(line).arg(col));
        AlertValidation *val = new AlertValidation();
        return *val;
    }

    QDomElement el = doc.documentElement();
    if (!el.tagName().compare(::XML_VALIDATION_ELEMENTTAG, Qt::CaseInsensitive) == 0)
        el = el.firstChildElement(::XML_VALIDATION_ELEMENTTAG);
    if (el.isNull()) {
        LOG_ERROR_FOR("AlertValidation", tkTr(Trans::Constants::XML_WRONG_NUMBER_OF_TAG_1).arg(::XML_VALIDATION_ELEMENTTAG));
        AlertValidation *val = new AlertValidation();
        return *val;
    }
    return fromDomElement(el);
}
