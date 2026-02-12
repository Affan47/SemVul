QString Display::findGreeterTheme() const {
        QString themeName = mainConfig.Theme.Current.get();


        if (themeName.isEmpty())
            return QString();

        QDir dir(mainConfig.Theme.ThemeDir.get());


        if (dir.exists(themeName))
            return dir.absoluteFilePath(themeName);


        qWarning() << "The configured theme" << themeName << "doesn't exist, using the embedded theme instead";
        return QString();
    }
