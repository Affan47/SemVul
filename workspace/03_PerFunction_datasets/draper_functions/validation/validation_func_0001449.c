complete_dialplan_add_extension(struct ast_cli_args *a)
{
	int which = 0;

	if (a->pos == 4) {
		return (a->n == 0) ? strdup("into") : NULL;
	} else if (a->pos == 5) {
		struct ast_context *c = NULL;
		int len = strlen(a->word);
		char *res = NULL;


		if (ast_rdlock_contexts()) {
			ast_log(LOG_WARNING, "Failed to lock contexts list\n");
			return NULL;
		}


		while ( !res && (c = ast_walk_contexts(c)) )
			if (partial_match(ast_get_context_name(c), a->word, len) && ++which > a->n)
				res = strdup(ast_get_context_name(c));
		ast_unlock_contexts();
		return res;
	} else if (a->pos == 6) {
		return a->n == 0 ? strdup("replace") : NULL;
	}
	return NULL;
}
