format_match_decimal_number (char const *text, GOFormatFamily *family,
			     gboolean try_alternates)
{
	GString const *curr = go_locale_get_currency (NULL, NULL);
	GString const *thousand = go_locale_get_thousand ();
	GString const *decimal = go_locale_get_decimal ();
	GnmValue *v;
	unsigned ui;

	v = format_match_decimal_number_with_locale (text, family, curr, thousand, decimal);
	for (ui = 0;
	     try_alternates && v == NULL && ui < G_N_ELEMENTS (alternate_currencies);
	     ui++) {
		const char *sym = alternate_currencies[ui].sym;
		if (strstr (text, sym) == 0)
			continue;
		else {
			GString *altcurr = g_string_new (sym);
			v = format_match_decimal_number_with_locale
				(text, family, altcurr, thousand, decimal);
			g_string_free (altcurr, TRUE);
			if (v)
				set_money_format (v, alternate_currencies[ui].fmt);
		}
	}

	return v;
}
