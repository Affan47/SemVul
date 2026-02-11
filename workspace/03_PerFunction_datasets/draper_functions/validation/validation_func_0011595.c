totem_uri_exists (const char *uri)
{
	GFile *file = g_file_new_for_uri (uri);
	if (file != NULL) {
		if (g_file_query_exists (file, NULL)) {
			g_object_unref (file);
			return TRUE;
		}
		g_object_unref (file);
	}
	return FALSE;
}
