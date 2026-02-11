nemo_file_get_parent_uri (NemoFile *file)
{
	g_assert (NEMO_IS_FILE (file));

	if (nemo_file_is_self_owned (file)) {

		return g_strdup ("");
	}

	return nemo_directory_get_uri (file->details->directory);
}
