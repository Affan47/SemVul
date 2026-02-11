complete_from_variables(const char *text, const char *prefix, const char *suffix,
						bool need_value)
{
	char	  **matches;
	char	  **varnames;
	int			nvars = 0;
	int			maxvars = 100;
	int			i;
	struct _variable *ptr;

	static const char *const known_varnames[] = {
		"AUTOCOMMIT", "COMP_KEYWORD_CASE", "DBNAME", "ECHO", "ECHO_HIDDEN",
		"ENCODING", "FETCH_COUNT", "HISTCONTROL", "HISTFILE", "HISTSIZE",
		"HOST", "IGNOREEOF", "LASTOID", "ON_ERROR_ROLLBACK", "ON_ERROR_STOP",
		"PORT", "PROMPT1", "PROMPT2", "PROMPT3", "QUIET",
		"SHOW_CONTEXT", "SINGLELINE", "SINGLESTEP",
		"USER", "VERBOSITY", NULL
	};

	varnames = (char **) pg_malloc((maxvars + 1) * sizeof(char *));

	if (!need_value)
	{
		for (i = 0; known_varnames[i] && nvars < maxvars; i++)
			append_variable_names(&varnames, &nvars, &maxvars,
								  known_varnames[i], prefix, suffix);
	}

	for (ptr = pset.vars->next; ptr; ptr = ptr->next)
	{
		if (need_value && !(ptr->value))
			continue;
		for (i = 0; known_varnames[i]; i++)
		{
			if (strcmp(ptr->name, known_varnames[i]) == 0)
				continue;
		}
		append_variable_names(&varnames, &nvars, &maxvars, ptr->name,
							  prefix, suffix);
	}

	varnames[nvars] = NULL;
	COMPLETE_WITH_LIST_CS((const char *const *) varnames);

	for (i = 0; i < nvars; i++)
		free(varnames[i]);
	free(varnames);

	return matches;
}
