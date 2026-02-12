nsdate_to_strftime (EmpathyAdiumData *data, const gchar *nsdate)
{


	static const gchar *convert_table[] = {
		"a", "%p",
		"A", NULL,

		"cccc", "%A",
		"ccc", "%a",
		"cc", "%u",
		"c", "%u",

		"dd", "%d",
		"d", "%d",
		"D", "%j",

		"e", "%u",
		"EEEE", "%A",
		"EEE", "%a",
		"EE", "%a",
		"E", "%a",

		"F", NULL,

		"g", NULL,
		"GGGG", NULL,
		"GGG", NULL,
		"GG", NULL,
		"G", NULL,

		"h", "%I",
		"H", "%H",

		"k", NULL,
		"K", NULL,

		"LLLL", "%B",
		"LLL", "%b",
		"LL", "%m",
		"L", "%m",

		"m", "%M",
		"MMMM", "%B",
		"MMM", "%b",
		"MM", "%m",
		"M", "%m",

		"qqqq", NULL,
		"qqq", NULL,
		"qq", NULL,
		"q", NULL,
		"QQQQ", NULL,
		"QQQ", NULL,
		"QQ", NULL,
		"Q", NULL,

		"s", "%S",
		"S", NULL,

		"u", "%Y",

		"vvvv", "%Z",
		"vvv", "%Z",
		"vv", "%Z",
		"v", "%Z",

		"w", "%W",
		"W", NULL,

		"yyyy", "%Y",
		"yyy", "%y",
		"yy", "%y",
		"y", "%Y",
		"YYYY", NULL,
		"YYY", NULL,
		"YY", NULL,
		"Y", NULL,

		"zzzz", NULL,
		"zzz", NULL,
		"zz", NULL,
		"z", NULL,
		"Z", "%z",
	};
	const gchar *str;
	GString *string;
	guint i, j;

	if (nsdate == NULL) {
		return NULL;
	}

	str = g_hash_table_lookup (data->date_format_cache, nsdate);
	if (str != NULL) {
		return str;
	}


	string = g_string_sized_new (strlen (nsdate));
	for (i = 0; nsdate[i] != '\0'; i++) {
		gboolean found = FALSE;


		for (j = 0; j < G_N_ELEMENTS (convert_table); j += 2) {
			if (g_str_has_prefix (nsdate + i, convert_table[j])) {
				found = TRUE;
				break;
			}
		}
		if (found) {

			if (convert_table[j + 1] != NULL) {
				g_string_append (string, convert_table[j + 1]);
			}
			i += strlen (convert_table[j]) - 1;
		} else {
			g_string_append_c (string, nsdate[i]);
		}
	}

	DEBUG ("Date format converted '%s' → '%s'", nsdate, string->str);


	g_hash_table_insert (data->date_format_cache, g_strdup (nsdate), string->str);
	return g_string_free (string, FALSE);
}
