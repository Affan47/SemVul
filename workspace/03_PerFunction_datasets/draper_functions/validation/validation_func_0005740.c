replace_string (gchar **string, const gchar *search, const char *replacement)
{
	GRegex *regex;
	gchar *res;

	g_return_val_if_fail (*string != NULL, NULL);
	g_return_val_if_fail (string != NULL, NULL);
	g_return_val_if_fail (search != NULL, *string);
	g_return_val_if_fail (replacement != NULL, *string);

	regex = g_regex_new (search, 0, 0, NULL);
	res = g_regex_replace_literal (regex, *string, -1, 0, replacement, 0, NULL);
	g_regex_unref (regex);

	g_free (*string);
	*string = res;

	return res;
}
