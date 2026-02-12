bool Display::findSessionEntry(const QDir &dir, const QString &name) const {
        QString fileName = name;


        const QString extension = QStringLiteral(".desktop");
        if (!fileName.endsWith(extension))
            fileName += extension;

        return dir.exists(fileName);
    }
