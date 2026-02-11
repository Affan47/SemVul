complete_indications(struct ast_cli_args *a)
{
	char *res = NULL;
	int which = 0;
	size_t wordlen;
	struct ast_tone_zone_sound *ts;
	struct ast_tone_zone *tz, tmp_tz = {
		.nrringcadence = 0,
	};

	ast_copy_string(tmp_tz.country, a->argv[a->pos - 1], sizeof(tmp_tz.country));

	if (!(tz = ao2_find(ast_tone_zones, &tmp_tz, OBJ_POINTER))) {
		return NULL;
	}

	wordlen = strlen(a->word);

	ast_tone_zone_lock(tz);
	AST_LIST_TRAVERSE(&tz->tones, ts, entry) {
		if (!strncasecmp(a->word, ts->name, wordlen) && ++which > a->n) {
			res = ast_strdup(ts->name);
			break;
		}
	}
	ast_tone_zone_unlock(tz);

	tz = ast_tone_zone_unref(tz);

	return res;
}
