getNextNumberedAttribute(TranslationTableHeader *table) {


	TranslationTableCharacterAttributes next = table->nextNumberedCharacterClassAttribute;
	if (next > CTC_UserDefined8) return 0;
	table->nextNumberedCharacterClassAttribute <<= 1;
	return next;
}
