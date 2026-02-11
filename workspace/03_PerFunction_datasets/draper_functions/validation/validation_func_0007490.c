remove_mnemonic_character (const gchar * string)
{
	GString * gs;
	gboolean first_mnemonic = TRUE;

	if (string == NULL) {
		return NULL;
	}

	gs = g_string_new ("");
	for(; *string; string++) {
		if ((first_mnemonic) && (*string == '_')) {
			first_mnemonic = FALSE;
			continue;
		}
		g_string_append_c(gs, *string);
	}
	return g_string_free (gs, FALSE);
}
