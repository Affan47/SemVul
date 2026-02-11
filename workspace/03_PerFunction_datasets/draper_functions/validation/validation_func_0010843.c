_g_file_has_prefix (GFile *file,
		    GFile *prefix)
{
	char     *file_uri;
	char     *prefix_uri;
	gboolean  result;

	file_uri = g_file_get_uri (file);
	prefix_uri = g_file_get_uri (prefix);
	if (! g_str_has_suffix (prefix_uri, "/")) {
		char *tmp;

		tmp = g_strconcat (prefix_uri, "/", NULL);
		g_free (prefix_uri);
		prefix_uri = tmp;
	}
	result = g_str_has_prefix (file_uri, prefix_uri);

	g_free (prefix_uri);
	g_free (file_uri);

	return result;
}
