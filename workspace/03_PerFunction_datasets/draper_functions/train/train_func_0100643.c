get_uri_perm (const char *uri, const char *perm_attribute)
{
	GFile *f;
	GFileInfo *info;
	GError *error = NULL;
	gboolean result;

	f = g_file_new_for_uri (uri);
	info = g_file_query_info (f, perm_attribute, 0, NULL, &error);
	if (error != NULL) {
		result = FALSE;
		g_error_free (error);
	} else {
		result = g_file_info_get_attribute_boolean (info, perm_attribute);
	}

	if (info != NULL) {
		g_object_unref (info);
	}
	g_object_unref (f);
	return result;
}
