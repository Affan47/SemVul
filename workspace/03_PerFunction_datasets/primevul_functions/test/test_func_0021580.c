addBackwardRuleWithSingleCell(const FileInfo *file, widechar cell,
		TranslationTableOffset ruleOffset, TranslationTableRule *rule,
		TranslationTableHeader **table) {

	TranslationTableCharacter *dots;
	if (rule->opcode == CTO_SwapCc || rule->opcode == CTO_Repeated)
		return;


	dots = putDots(file, cell, table);

	rule = (TranslationTableRule *)&(*table)->ruleArea[ruleOffset];
	if (rule->opcode >= CTO_Space && rule->opcode < CTO_UpLow)
		dots->definitionRule = ruleOffset;
	TranslationTableOffset *otherRule = &dots->otherRules;
	while (*otherRule) {
		TranslationTableRule *r = (TranslationTableRule *)&(*table)->ruleArea[*otherRule];
		if (rule->charslen > r->charslen || r->dotslen == 0) break;
		if (r->opcode >= CTO_Space && r->opcode < CTO_UpLow)
			if (!(rule->opcode >= CTO_Space && rule->opcode < CTO_UpLow)) break;
		otherRule = &r->dotsnext;
	}
	rule->dotsnext = *otherRule;
	*otherRule = ruleOffset;
}
