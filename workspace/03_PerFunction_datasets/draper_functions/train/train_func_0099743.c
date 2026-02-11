expand_regex_vars (ParserState *parser_state, gchar *regex, gint len, GError **error)
{


	const gchar *re = "(?<!\\\\)(\\\\\\\\)*\\\\%\\{([^@]*?)\\}";
	gchar *expanded_regex;
	GRegex *egg_re;
	struct ReplaceByIdData data;

	if (regex == NULL)
		return NULL;

	egg_re = g_regex_new (re, G_REGEX_NEWLINE_LF, 0, NULL);

	data.parser_state = parser_state;
	data.error = NULL;
	expanded_regex = g_regex_replace_eval (egg_re, regex, len, 0, 0,
					       replace_by_id, &data, NULL);

	if (data.error == NULL)
        {
		DEBUG (g_message ("expanded regex vars '%s' to '%s'",
				  regex, expanded_regex));
        }

	g_regex_unref (egg_re);

	if (data.error != NULL)
	{
		g_free (expanded_regex);
		g_propagate_error (error, data.error);
		return NULL;
	}

	return expanded_regex;
}
