compileTable(const char *tableList, const char *displayTableList,
		TranslationTableHeader **translationTable, DisplayTableHeader **displayTable) {
	char **tableFiles;
	char **subTable;
	if (translationTable && !tableList) return 0;
	if (displayTable && !displayTableList) return 0;
	if (!translationTable && !displayTable) return 0;
	if (translationTable) *translationTable = NULL;
	if (displayTable) *displayTable = NULL;
	errorCount = warningCount = fileCount = 0;
	if (!opcodeLengths[0]) {
		TranslationTableOpcode opcode;
		for (opcode = 0; opcode < CTO_None; opcode++)
			opcodeLengths[opcode] = (short)strlen(opcodeNames[opcode]);
	}
	if (translationTable) allocateTranslationTable(NULL, translationTable);
	if (displayTable) allocateDisplayTable(NULL, displayTable);

	if (translationTable) {
		(*translationTable)->emphClassNames[0] = NULL;
		(*translationTable)->characterClasses = NULL;
		(*translationTable)->ruleNames = NULL;
	}


	compileString("space \\xffff 123456789abcdef LOU_ENDSEGMENT", translationTable,
			displayTable);

	if (displayTable && translationTable && strcmp(tableList, displayTableList) == 0) {


		if (!(tableFiles = _lou_resolveTable(tableList, NULL))) {
			errorCount++;
			goto cleanup;
		}
		for (subTable = tableFiles; *subTable; subTable++)
			if (!compileFile(*subTable, translationTable, displayTable)) goto cleanup;
	} else {


		if (displayTable) {
			if (!(tableFiles = _lou_resolveTable(displayTableList, NULL))) {
				errorCount++;
				goto cleanup;
			}
			for (subTable = tableFiles; *subTable; subTable++)
				if (!compileFile(*subTable, NULL, displayTable)) goto cleanup;
			free_tablefiles(tableFiles);
			tableFiles = NULL;
		}
		if (translationTable) {
			if (!(tableFiles = _lou_resolveTable(tableList, NULL))) {
				errorCount++;
				goto cleanup;
			}
			for (subTable = tableFiles; *subTable; subTable++)
				if (!compileFile(*subTable, translationTable, NULL)) goto cleanup;
		}
	}


cleanup:
	free_tablefiles(tableFiles);
	if (warningCount) _lou_logMessage(LOU_LOG_WARN, "%d warnings issued", warningCount);
	if (!errorCount) {
		if (translationTable) setDefaults(*translationTable);
		return 1;
	} else {
		_lou_logMessage(LOU_LOG_ERROR, "%d errors found.", errorCount);
		if (translationTable) {
			if (*translationTable) freeTranslationTable(*translationTable);
			*translationTable = NULL;
		}
		if (displayTable) {
			if (*displayTable) free(*displayTable);
			*displayTable = NULL;
		}
		return 0;
	}
}
