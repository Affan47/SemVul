convert_language_code (gchar *code)
{
	size_t i;
	for (i = 0; lingua[i].ispell; i++) {
	        if (!strcmp(code,lingua[i].ispell)) {

		        return g_strdup (lingua[i].enchant);
		}
	}

	return g_strdup (code);
}
