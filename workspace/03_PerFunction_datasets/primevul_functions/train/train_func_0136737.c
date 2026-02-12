allocateSpaceInTable(FileInfo *nested, TranslationTableOffset *offset, int count,
		TranslationTableHeader **table) {


	int spaceNeeded = ((count + OFFSETSIZE - 1) / OFFSETSIZE) * OFFSETSIZE;
	TranslationTableOffset size = tableUsed + spaceNeeded;
	if (size > tableSize) {
		TranslationTableHeader *newTable;
		size += (size / OFFSETSIZE);
		newTable = realloc(*table, size);
		if (!newTable) {
			compileError(nested, "Not enough memory for translation table.");
			_lou_outOfMemory();
		}
		memset(((unsigned char *)newTable) + tableSize, 0, size - tableSize);

		{
			ChainEntry *entry;
			for (entry = tableChain; entry != NULL; entry = entry->next)
				if (entry->table == *table)
					entry->table = (TranslationTableHeader *)newTable;
		}
		*table = (TranslationTableHeader *)newTable;
		tableSize = size;
	}
	if (offset != NULL) {
		*offset = (tableUsed - sizeof(**table)) / OFFSETSIZE;
		tableUsed += spaceNeeded;
	}
	return 1;
}
