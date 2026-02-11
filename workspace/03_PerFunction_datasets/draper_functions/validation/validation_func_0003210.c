constructStyleSheet(const QString &extraStyleSheet)
    {
        QStringList css;


        css << QString("padding-left: %1px").arg(_leftPadding);
        css << QString("padding-right: %1px").arg(_rightPadding);


        if (!extraStyleSheet.isEmpty()) {
            foreach(const QString &c, extraStyleSheet.split(";", QString::SkipEmptyParts)) {
                if (!c.startsWith("paddin",Qt::CaseInsensitive))
                    css << c;
            }
        }
        return QString("%1;").arg(css.join(";"));
    }
