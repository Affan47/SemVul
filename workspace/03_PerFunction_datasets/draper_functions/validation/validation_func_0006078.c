_g_file_get_standard_type (GFile *file)
{
	GFileType  result;
	GFileInfo *info;
	GError    *error = NULL;

	info = g_file_query_info (file, G_FILE_ATTRIBUTE_STANDARD_TYPE, 0, NULL, &error);
	if (error == NULL) {
		result = g_file_info_get_file_type (info);
	}
	else {
		result = G_FILE_ATTRIBUTE_TYPE_INVALID;
		g_error_free (error);
	}

	if (info != NULL)
		g_object_unref (info);

	return result;
}
