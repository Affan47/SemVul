loadActionPacks(const QString &directory, const QString &locale)
	{
#ifdef ACT_PROFILE
		Tools::HighResolutionTimer timer("ActionFactory loadActionPacks from " + directory);
#endif

		QDir actionDirectory(directory);

#ifdef Q_WS_WIN
		QString actionMask = "ActionPack*.dll";
#endif
#ifdef Q_WS_MAC
		QString actionMask = "libActionPack*.dylib";
#endif
#ifdef Q_WS_X11
		QString actionMask = "libActionPack*.so";
#endif

		foreach(const QString actionFilename, actionDirectory.entryList(QStringList() << actionMask, QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks))
			loadActionPack(actionDirectory.absoluteFilePath(actionFilename), locale);

		qSort(mActionDefinitions.begin(), mActionDefinitions.end(), actionDefinitionLessThan);

		for(int index = 0; index < mActionDefinitions.count(); ++index)
			mActionDefinitions.at(index)->setIndex(index);
	}
