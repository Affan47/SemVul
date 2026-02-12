compile_findCharOrDots(widechar c, int m, TranslationTableHeader *table) {


	TranslationTableCharacter *character;
	TranslationTableOffset bucket;
	unsigned long int makeHash = (unsigned long int)c % HASHNUM;
	if (m == 0)
		bucket = table->characters[makeHash];
	else
		bucket = table->dots[makeHash];
	while (bucket) {
		character = (TranslationTableCharacter *)&table->ruleArea[bucket];
		if (character->realchar == c) return character;
		bucket = character->next;
	}
	return NULL;
}
