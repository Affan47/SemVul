getTrLanguages(const QString &absPath)
    {
        LanguageList trLanguages;
        QStringList qms = findQmFiles(absPath);
        for (int i = 0; i < qms.size(); ++i)
        {
            QLocale locale(qms[i]);
            if (locale.language() == QLocale::C)
                continue;
            trLanguages.push_back(Language(locale.language()));
        }
        trLanguages.append(QLocale::English);
        qSort(trLanguages);
        trLanguages.prepend(Language(QLocale::C));
        return trLanguages;
    }
