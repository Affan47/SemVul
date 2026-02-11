guess_time_format (const char *prefix, gnm_float f)
{
	int decs = 0;
	gnm_float eps = 1e-6;
	static int maxdecs = 6;
	GString *str = g_string_new (prefix);
	GOFormat *fmt;

	if (f >= 0 && f < 1)
		g_string_append (str, "hh:mm");
	else
		g_string_append (str, "[h]:mm");
	f *= 24 * 60;
	if (!close_to_int (f, eps / 60)) {
		g_string_append (str, ":ss");
		f *= 60;
		if (!close_to_int (f, eps)) {
			g_string_append_c (str, '.');
			while (decs < maxdecs) {
				decs++;
				g_string_append_c (str, '0');
				f *= 10;
				if (close_to_int (f, eps))
					break;
			}
		}
	}

	while (go_format_is_invalid ((fmt = go_format_new_from_XL (str->str))) && decs > 0) {

		go_format_unref (fmt);
		maxdecs = --decs;
		g_string_truncate (str, str->len - 1);
	}

	g_string_free (str, TRUE);
	return fmt;
}
