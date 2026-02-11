_check_file (GFile *mount_root, const char *file_path, gboolean must_be_executable)
{
	GFile *file;
	GFileInfo *file_info;
	gboolean ret;

	ret = FALSE;

	file = g_file_get_child (mount_root, file_path);
	file_info = g_file_query_info (file,
				       G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE,
				       G_FILE_QUERY_INFO_NONE,
				       NULL,
				       NULL);
	if (file_info != NULL) {
		if (must_be_executable) {
			if (g_file_info_get_attribute_boolean (file_info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE)) {
				ret = TRUE;
			}
		} else {
			ret = TRUE;
		}
		g_object_unref (file_info);
	}
	g_object_unref (file);

	return ret;
}
