getTable(const char *translationTableList, const char *displayTableList,
		TranslationTableHeader **translationTable, DisplayTableHeader **displayTable) {

	int translationTableListLen, displayTableListLen = 0;
	if (translationTableList == NULL || *translationTableList == 0)
		translationTable = NULL;
	if (displayTableList == NULL || *displayTableList == 0) displayTable = NULL;

	if (translationTable) {
		translationTableListLen = (int)strlen(translationTableList);
		*translationTable = NULL;
		TranslationTableChainEntry *currentEntry = translationTableChain;
		TranslationTableChainEntry *prevEntry = NULL;
		while (currentEntry != NULL) {
			if (translationTableListLen == currentEntry->tableListLength &&
					(memcmp(&currentEntry->tableList[0], translationTableList,
							translationTableListLen)) == 0) {

				if (prevEntry != NULL) {
					prevEntry->next = currentEntry->next;
					currentEntry->next = translationTableChain;
					translationTableChain = currentEntry;
				}
				*translationTable = currentEntry->table;
				break;
			}
			prevEntry = currentEntry;
			currentEntry = currentEntry->next;
		}
	}

	if (displayTable) {
		displayTableListLen = (int)strlen(displayTableList);
		*displayTable = NULL;
		DisplayTableChainEntry *currentEntry = displayTableChain;
		DisplayTableChainEntry *prevEntry = NULL;
		while (currentEntry != NULL) {
			if (displayTableListLen == currentEntry->tableListLength &&
					(memcmp(&currentEntry->tableList[0], displayTableList,
							displayTableListLen)) == 0) {

				if (prevEntry != NULL) {
					prevEntry->next = currentEntry->next;
					currentEntry->next = displayTableChain;
					displayTableChain = currentEntry;
				}
				*displayTable = currentEntry->table;
				break;
			}
			prevEntry = currentEntry;
			currentEntry = currentEntry->next;
		}
	}
	if ((translationTable && *translationTable == NULL) ||
			(displayTable && *displayTable == NULL)) {
		TranslationTableHeader *newTranslationTable = NULL;
		DisplayTableHeader *newDisplayTable = NULL;
		if (compileTable(translationTableList, displayTableList,
					(translationTable && *translationTable == NULL) ? &newTranslationTable
																	: NULL,
					(displayTable && *displayTable == NULL) ? &newDisplayTable : NULL)) {

			if (newTranslationTable != NULL) {
				int entrySize =
						sizeof(TranslationTableChainEntry) + translationTableListLen;
				TranslationTableChainEntry *newEntry = malloc(entrySize);
				if (!newEntry) _lou_outOfMemory();
				newEntry->next = translationTableChain;
				newEntry->table = newTranslationTable;
				newEntry->tableListLength = translationTableListLen;
				memcpy(&newEntry->tableList[0], translationTableList,
						translationTableListLen);
				translationTableChain = newEntry;
				*translationTable = newTranslationTable;
			}
			if (newDisplayTable != NULL) {
				int entrySize = sizeof(DisplayTableChainEntry) + displayTableListLen;
				DisplayTableChainEntry *newEntry = malloc(entrySize);
				if (!newEntry) _lou_outOfMemory();
				newEntry->next = displayTableChain;
				newEntry->table = newDisplayTable;
				newEntry->tableListLength = displayTableListLen;
				memcpy(&newEntry->tableList[0], displayTableList, displayTableListLen);
				displayTableChain = newEntry;
				*displayTable = newDisplayTable;
			}
		} else {
			_lou_logMessage(
					LOU_LOG_ERROR, "%s could not be compiled", translationTableList);
			return;
		}
	}
}
