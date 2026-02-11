gfire_remove_quake3_color_codes(const gchar *p_string)
{
	if(!p_string)
		return NULL;

	const gchar color_codes[] =
	{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z',
		'?', '+', '@', '-', '_', '/', '&', '(', '>', '.'
	};

	gchar *escaped = g_strdup(p_string);

	int i;
	gchar code[3];
	gchar *tmp = NULL;

	for (i = 0; i < sizeof(color_codes); i++)
	{
		g_snprintf(code, 3, "^%c", color_codes[i]);
		tmp = purple_strcasereplace(escaped, code, "");
		g_free(escaped);
		escaped = tmp;
	}

	return escaped;
}
