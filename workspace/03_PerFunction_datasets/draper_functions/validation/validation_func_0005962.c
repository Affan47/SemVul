xpm_extract_color (const gchar *buffer)
{
	const gchar *p = &buffer[0];
	gint new_key = 0;
	gint key = 0;
	gint current_key = 1;
	gint space = 128;
	gchar word[129], color[129], current_color[129];
	gchar *r;

	word[0] = '\0';
	color[0] = '\0';
	current_color[0] = '\0';
        while (1) {

		for (; *p != '\0' && g_ascii_isspace (*p); p++) {
		}

		for (r = word; *p != '\0' && !g_ascii_isspace (*p) && r - word < sizeof (word) - 1; p++, r++) {
			*r = *p;
		}
		*r = '\0';
		if (*word == '\0') {
			if (color[0] == '\0')
				return NULL;
			else
				new_key = 1;
		}
		else if (key > 0 && color[0] == '\0')
			new_key = 0;
		else {
			if (strcmp (word, "c") == 0)
				new_key = 5;
			else if (strcmp (word, "g") == 0)
				new_key = 4;
			else if (strcmp (word, "g4") == 0)
				new_key = 3;
			else if (strcmp (word, "m") == 0)
				new_key = 2;
			else if (strcmp (word, "s") == 0)
				new_key = 1;
			else
				new_key = 0;
		}
		if (new_key == 0) {
			if (key == 0)
				return NULL;

			if (color[0] != '\0') {
				strncat (color, " ", space);
				space -= MIN (space, 1);
			}
			strncat (color, word, space);
			space -= MIN (space, strlen (word));
		}
		else {
			if (key > current_key) {
				current_key = key;
				strcpy (current_color, color);
			}
			space = 128;
			color[0] = '\0';
			key = new_key;
			if (*p == '\0') break;
		}

	}
	if (current_key > 1)
		return g_strdup (current_color);
	else
		return NULL;
}
