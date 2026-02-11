my_g_file_info_get_mime_type_with_data (GFile *file, gpointer *data, TotemPlParser *parser)
{
	char *buffer;
	gsize bytes_read;
	GFileInputStream *stream;
	GError *error = NULL;

	*data = NULL;

#ifndef _WIN32


	if (g_file_is_native (file) != FALSE) {
		struct stat buf;
		char *path;

		path = g_file_get_path (file);
		if (g_stat (path, &buf) == 0 && S_ISBLK (buf.st_mode)) {
			g_free (path);
			return g_strdup (BLOCK_DEVICE_TYPE);
		}
		g_free (path);
	}
#endif


	stream = g_file_read (file, NULL, &error);
	if (stream == NULL) {
		if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_IS_DIRECTORY) != FALSE) {
			g_error_free (error);
			return g_strdup (DIR_MIME_TYPE);
		}
		DEBUG(file, g_print ("URI '%s' couldn't be opened in _get_mime_type_with_data: '%s'\n", uri, error->message));
		g_error_free (error);
		return NULL;
	}
	DEBUG(file, g_print ("URI '%s' was opened successfully in _get_mime_type_with_data\n", uri));


	buffer = g_malloc (MIME_READ_CHUNK_SIZE);
	if (g_input_stream_read_all (G_INPUT_STREAM (stream), buffer, MIME_READ_CHUNK_SIZE, &bytes_read, NULL, &error) == FALSE) {
		g_object_unref (stream);
		DEBUG(file, g_print ("Couldn't read data from '%s'\n", uri));
		g_free (buffer);
		return NULL;
	}
	g_object_unref (G_INPUT_STREAM (stream));


	if (bytes_read == 0) {
		g_free (buffer);
		DEBUG(file, g_print ("URI '%s' is empty in _get_mime_type_with_data\n", uri));
		return g_strdup (EMPTY_FILE_TYPE);
	}


	buffer = g_realloc (buffer, bytes_read + 1);
	buffer[bytes_read] = '\0';
	*data = buffer;

	return totem_pl_parser_mime_type_from_data (*data, bytes_read);
}
