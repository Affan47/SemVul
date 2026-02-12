getNextAttribute(TranslationTableHeader *table) {

	TranslationTableCharacterAttributes next = table->nextCharacterClassAttribute;
	if (next) {
		if (next == CTC_LitDigit)
			table->nextCharacterClassAttribute = CTC_UserDefined9;
		else
			table->nextCharacterClassAttribute <<= 1;
		return next;
	} else
		return getNextNumberedAttribute(table);
}
