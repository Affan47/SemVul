camel_search_words_split (const guchar *in)
{
	gint type = CAMEL_SEARCH_WORD_SIMPLE, all = 0;
	GString *w;
	struct _camel_search_words *words;
	GPtrArray *list = g_ptr_array_new ();
	guint32 c;
	gint inquote = 0;

	words = g_malloc0 (sizeof (*words));
	w = g_string_new ("");

	do {
		c = camel_utf8_getc (&in);

		if (c == 0
		    || (inquote && c == '"')
		    || (!inquote && g_unichar_isspace (c))) {
			output_w (w, list, type);
			all |= type;
			type = CAMEL_SEARCH_WORD_SIMPLE;
			inquote = 0;
		} else {
			if (c == '\\') {
				c = camel_utf8_getc (&in);
				if (c)
					output_c (w, c, &type);
				else {
					output_w (w, list, type);
					all |= type;
				}
			} else if (c == '\"') {
				inquote = 1;
			} else {
				output_c (w, c, &type);
			}
		}
	} while (c);

	g_string_free (w, TRUE);
	words->len = list->len;
	words->words = (struct _camel_search_word **) list->pdata;
	words->type = all;
	g_ptr_array_free (list, FALSE);

	return words;
}
