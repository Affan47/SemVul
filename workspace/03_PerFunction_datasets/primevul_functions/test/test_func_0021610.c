finalizeTable(TranslationTableHeader *table) {
	if (table->finalized) return 1;

	for (int i = 0; i < HASHNUM; i++) {
		TranslationTableOffset characterOffset = table->characters[i];
		while (characterOffset) {
			TranslationTableCharacter *character =
					(TranslationTableCharacter *)&table->ruleArea[characterOffset];
			if (character->basechar) {
				TranslationTableOffset basecharOffset = 0;
				TranslationTableCharacter *basechar = character;
				TranslationTableCharacterAttributes mode = 0;
				int detect_loop = 0;
				while (basechar->basechar) {
					if (basechar->basechar == characterOffset ||
							detect_loop++ > MAX_MODES) {
						_lou_logMessage(LOU_LOG_ERROR,
								"%s: error: Character can not be (indirectly) based on "
								"itself.",
								printSource(NULL, character->sourceFile,
										character->sourceLine));
						errorCount++;
						return 0;
					}

					mode |= basechar->mode;

					basecharOffset = basechar->basechar;
					basechar =
							(TranslationTableCharacter *)&table->ruleArea[basecharOffset];
					if (character->mode & (basechar->attributes | basechar->mode)) {
						char *attributeName = NULL;
						const CharacterClass *class = table->characterClasses;
						while (class) {
							if (class->attribute == character->mode) {
								attributeName = strdup(
										_lou_showString(class->name, class->length, 0));
								break;
							}
							class = class->next;
						}
						_lou_logMessage(LOU_LOG_ERROR,
								"%s: error: Base character %s can not have the %s "
								"attribute.",
								printSource(NULL, character->sourceFile,
										character->sourceLine),
								_lou_showString(&basechar->value, 1, 0),
								attributeName != NULL ? attributeName : "?");
						errorCount++;
						free(attributeName);
						return 0;
					}
				}
				character->mode = mode;
				character->basechar = basecharOffset;

				character->attributes |= character->mode;
				if (character->attributes & (CTC_UpperCase | CTC_LowerCase))
					character->attributes |= CTC_Letter;


				TranslationTableRule *defRule =
						(TranslationTableRule *)&table
								->ruleArea[basechar->definitionRule];
				if (defRule->dotslen == 1) {
					TranslationTableCharacter *dots =
							getDots(defRule->charsdots[defRule->charslen], table);
					if (dots) {
						dots->attributes |= character->mode;
						if (dots->attributes & (CTC_UpperCase | CTC_LowerCase))
							dots->attributes |= CTC_Letter;
					}
				}

				if (basechar->linked) character->linked = basechar->linked;
				basechar->linked = characterOffset;
			}
			characterOffset = character->next;
		}
	}

	for (int i = 0; i < HASHNUM; i++) {
		TranslationTableOffset characterOffset = table->characters[i];
		while (characterOffset) {
			TranslationTableCharacter *character =
					(TranslationTableCharacter *)&table->ruleArea[characterOffset];
			if (character->attributes & CTC_Letter) {
				TranslationTableOffset *otherRule = &character->otherRules;
				while (*otherRule) {
					TranslationTableRule *rule =
							(TranslationTableRule *)&table->ruleArea[*otherRule];
					if (rule->opcode == CTO_WholeWord || rule->opcode == CTO_LargeSign)
						if (table->noLetsignCount < LETSIGNSIZE)
							table->noLetsign[table->noLetsignCount++] =
									rule->charsdots[0];
					otherRule = &rule->charsnext;
				}
			}
			characterOffset = character->next;
		}
	}
	table->finalized = 1;
	return 1;
}
