nm_utils_ssid_to_utf8 (const GByteArray *ssid)
{
	char *converted = NULL;
	char *lang, *e1 = NULL, *e2 = NULL, *e3 = NULL;

	g_return_val_if_fail (ssid != NULL, NULL);

	if (g_utf8_validate ((const gchar *) ssid->data, ssid->len, NULL))
		return g_strndup ((const gchar *) ssid->data, ssid->len);


	g_get_charset ((const char **)(&e1));
	if ((lang = getenv ("LANG"))) {
		char * dot;

		lang = g_ascii_strdown (lang, -1);
		if ((dot = strchr (lang, '.')))
			*dot = '\0';

		get_encodings_for_lang (lang, &e1, &e2, &e3);
		g_free (lang);
	}

	converted = g_convert ((const gchar *) ssid->data, ssid->len, "UTF-8", e1, NULL, NULL, NULL);
	if (!converted && e2)
		converted = g_convert ((const gchar *) ssid->data, ssid->len, "UTF-8", e2, NULL, NULL, NULL);

	if (!converted && e3)
		converted = g_convert ((const gchar *) ssid->data, ssid->len, "UTF-8", e3, NULL, NULL, NULL);

	if (!converted) {
		converted = g_convert_with_fallback ((const gchar *) ssid->data, ssid->len,
		                                     "UTF-8", e1, "?", NULL, NULL, NULL);
	}

	return converted;
}
