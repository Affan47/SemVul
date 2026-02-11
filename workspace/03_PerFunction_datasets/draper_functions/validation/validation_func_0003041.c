autocomplete_html(ScintillaObject *sci, const gchar *root, gsize rootlen)
{
	guint i;
	gboolean found = FALSE;
	GString *words;
	const gchar **entities = symbols_get_html_entities();

	if (*root != '&' || entities == NULL)
		return FALSE;

	words = g_string_sized_new(500);
	for (i = 0; ; i++)
	{
		if (entities[i] == NULL)
			break;
		else if (entities[i][0] == '#')
			continue;

		if (! strncmp(entities[i], root, rootlen))
		{
			if (words->len)
				g_string_append_c(words, '\n');

			g_string_append(words, entities[i]);
			found = TRUE;
		}
	}
	if (found)
		show_autocomplete(sci, rootlen, words);

	g_string_free(words, TRUE);
	return found;
}
