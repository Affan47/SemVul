addForwardRuleWithSingleChar(const FileInfo *file, TranslationTableOffset ruleOffset,
		TranslationTableRule *rule, TranslationTableHeader **table) {

	TranslationTableCharacter *character;


	if (rule->opcode >= CTO_Pass2 && rule->opcode <= CTO_Pass4) {
		character = putDots(file, rule->charsdots[0], table);

		rule = (TranslationTableRule *)&(*table)->ruleArea[ruleOffset];
	} else if (rule->opcode == CTO_CompDots || rule->opcode == CTO_Comp6) {
		character = putChar(file, rule->charsdots[0], table, NULL);

		rule = (TranslationTableRule *)&(*table)->ruleArea[ruleOffset];
		character->compRule = ruleOffset;
		return;
	} else {
		character = putChar(file, rule->charsdots[0], table, NULL);

		rule = (TranslationTableRule *)&(*table)->ruleArea[ruleOffset];


		if (rule->opcode >= CTO_Space && rule->opcode < CTO_UpLow) {
			if (character->definitionRule) {
				TranslationTableRule *prevRule =
						(TranslationTableRule *)&(*table)
								->ruleArea[character->definitionRule];
				_lou_logMessage(LOU_LOG_DEBUG,
						"%s:%d: Character already defined (%s). The new definition will "
						"take precedence.",
						file->fileName, file->lineNumber,
						printSource(file, prevRule->sourceFile, prevRule->sourceLine));
			} else if (character->basechar) {
				_lou_logMessage(LOU_LOG_DEBUG,
						"%s:%d: A base rule already exists for this character (%s). The "
						"%s rule will take precedence.",
						file->fileName, file->lineNumber,
						printSource(file, character->sourceFile, character->sourceLine),
						_lou_findOpcodeName(rule->opcode));
				character->basechar = 0;
				character->mode = 0;
			}
			character->definitionRule = ruleOffset;
		}
	}


	TranslationTableOffset *otherRule = &character->otherRules;
	while (*otherRule) {
		TranslationTableRule *r = (TranslationTableRule *)&(*table)->ruleArea[*otherRule];
		if (r->charslen == 0) break;
		if (r->opcode >= CTO_Space && r->opcode < CTO_UpLow)
			if (!(rule->opcode >= CTO_Space && rule->opcode < CTO_UpLow)) break;
		otherRule = &r->charsnext;
	}
	rule->charsnext = *otherRule;
	*otherRule = ruleOffset;
}
