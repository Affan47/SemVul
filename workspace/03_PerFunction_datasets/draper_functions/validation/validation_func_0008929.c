guess_date_sep (void)
{
	const GString *df = go_locale_get_date_format();
	const char *s;

	for (s = df->str; *s; s++) {
		switch (*s) {
		case 'd': case 'm': case 'y':
			while (g_ascii_isalpha (*s))
				s++;
			while (g_unichar_isspace (g_utf8_get_char (s)))
				s = g_utf8_next_char (s);
			if (*s != ',' &&
			    g_unichar_ispunct (g_utf8_get_char (s)))
				return g_utf8_get_char (s);
			break;
		default:
			;
		}
	}

	return '/';
}
