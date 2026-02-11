loadParts(bool dbExists) {
	QStringList nameFilters;
	nameFilters << "*" + FritzingPartExtension;

	JustAppendAllPartsInstances = true;


	if (FirstTime) {
	}

	int totalPartCount = 0;
	emit loadedPart(0, totalPartCount);

	QDir * dir1 = FolderUtils::getApplicationSubFolder("parts");
	if (dir1 != NULL) {
		countParts(*dir1, nameFilters, totalPartCount);
	}
	QDir dir2(FolderUtils::getUserDataStorePath("parts"));
	countParts(dir2, nameFilters, totalPartCount);

	QDir dir3(":/resources/parts");
    if (m_fullLoad || !dbExists) {
	    countParts(dir3, nameFilters, totalPartCount);
    }

	int loadingPart = 0;
	if (dir1 != NULL) {
		loadPartsAux(*dir1, nameFilters, loadingPart, totalPartCount);
		delete dir1;
	}

	loadPartsAux(dir2, nameFilters, loadingPart, totalPartCount);

    if (m_fullLoad || !dbExists) {

	    loadPartsAux(dir3, nameFilters, loadingPart, totalPartCount);
    }

	if (FirstTime) {
	}

	JustAppendAllPartsInstances = false;


	FirstTime = false;

}
