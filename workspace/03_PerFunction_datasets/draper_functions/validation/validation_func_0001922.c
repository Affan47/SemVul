string_to_utf8 (MonoString *s)
{
	char *as;
	GError *error = NULL;

	g_assert (s);

	if (!s->length)
		return g_strdup ("");

	as = g_utf16_to_utf8 (mono_string_chars (s), s->length, NULL, NULL, &error);
	if (error) {

		g_error_free (error);
		return g_strdup ("<INVALID UTF8>");
	}
	else
		return as;
}
