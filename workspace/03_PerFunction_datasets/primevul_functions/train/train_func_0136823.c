allocateHeader(FileInfo *nested, TranslationTableHeader **table) {


	const TranslationTableOffset startSize = 2 * sizeof(**table);
	if (*table) return 1;
	tableUsed = sizeof(**table) + OFFSETSIZE;
	if (!(*table = malloc(startSize))) {
		compileError(nested, "Not enough memory");
		if (*table != NULL) free(*table);
		*table = NULL;
		_lou_outOfMemory();
	}
	memset(*table, 0, startSize);
	tableSize = startSize;
	return 1;
}
