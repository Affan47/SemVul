findCharacterClass(const CharsString *name, CharacterClass *characterClasses) {

	const CharacterClass *class = characterClasses;
	while (class) {
		if ((name->length == class->length) &&
				(memcmp(&name->chars[0], class->name, CHARSIZE * name->length) == 0))
			return class;
		class = class->next;
	}
	return NULL;
}
