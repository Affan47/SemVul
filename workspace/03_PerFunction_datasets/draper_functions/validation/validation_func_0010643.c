ilanguage_get_language (IAnjutaEditorLanguage *ilanguage, GError **err)
{
	const gchar *language = NULL;
	const gchar *filename = NULL;
	TextEditor *te = TEXT_EDITOR (ilanguage);

	if (te->force_hilite)
		filename = te->force_hilite;
	else if (te->filename)
		filename = te->filename;

	if (filename)
	{
		gchar *lexer = NULL;
		lexer = sci_prop_get_new_expand (te->props_base,
										 "lexer.", filename);


		if (lexer)
		{
			if (!supported_languages_by_lexer)
				ilanguage_get_supported_languages (ilanguage, NULL);

			language = g_hash_table_lookup (supported_languages_by_lexer, lexer);

			g_free (lexer);
		}
	}
	return language;
}
