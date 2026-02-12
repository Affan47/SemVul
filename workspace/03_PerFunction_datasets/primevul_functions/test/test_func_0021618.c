allocateCharacterClasses(TranslationTableHeader *table) {

	int k = 0;
	table->characterClasses = NULL;
	table->nextCharacterClassAttribute = 1;
	table->nextNumberedCharacterClassAttribute = CTC_UserDefined1;
	while (characterClassNames[k]) {
		widechar wname[MAXSTRING];
		int length = (int)strlen(characterClassNames[k]);
		int kk;
		for (kk = 0; kk < length; kk++) wname[kk] = (widechar)characterClassNames[k][kk];
		if (!addCharacterClass(NULL, wname, length, table, 0)) {
			deallocateCharacterClasses(table);
			return 0;
		}
		k++;
	}
	return 1;
}
