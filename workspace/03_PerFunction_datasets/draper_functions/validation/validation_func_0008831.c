cert_parser (NMSetting *setting, const char *key, GKeyFile *keyfile, const char *keyfile_path)
{
	const char *setting_name = nm_setting_get_name (setting);
	GByteArray *array;
	gboolean success = FALSE;

	array = get_uchar_array (keyfile, setting_name, key, TRUE, FALSE);
	if (array && array->len > 0) {

		success = handle_as_scheme (array, setting, key);


		if (success == FALSE)
			success = handle_as_path (array, setting, key, keyfile_path);


		if (success == FALSE)
			g_object_set (setting, key, array, NULL);
	} else {
		g_warning ("%s: ignoring invalid key/cert value for %s / %s",
		           __func__, setting_name, key);
	}

	if (array)
		g_byte_array_free (array, TRUE);
}
