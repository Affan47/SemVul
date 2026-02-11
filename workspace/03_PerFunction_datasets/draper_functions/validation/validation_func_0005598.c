loadBundledPart(const QString &fileName, bool addToBin) {
	QDir destFolder = QDir::temp();

	FolderUtils::createFolderAnCdIntoIt(destFolder, TextUtils::getRandText());
	QString unzipDirPath = destFolder.path();

    QString error;
	if(!FolderUtils::unzipTo(fileName, unzipDirPath, error)) {
		FMessageBox::warning(
			this,
			tr("Fritzing"),
			tr("Unable to open shareable part '%1': %2").arg(fileName).arg(error)
		);
		return NULL;
	}

	QDir unzipDir(unzipDirPath);

    QList<ModelPart*> mps;
    try {
	    mps = moveToPartsFolder(unzipDir, this, addToBin, true, FolderUtils::getUserDataStorePath("parts"), "user", true);
    }
    catch (const QString & msg) {
		FMessageBox::warning(
			this,
			tr("Fritzing"),
			msg
		);
        return NULL;
    }

	if (mps.count() != 1) {

		FMessageBox::warning(
			this,
			tr("Fritzing"),
			tr("Unable to load part from '%1'").arg(fileName)
		);
		return NULL;
	}

	FolderUtils::rmdir(unzipDirPath);

	return mps[0];
}
