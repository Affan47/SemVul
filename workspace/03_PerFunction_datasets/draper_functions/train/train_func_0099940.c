save_response_to_cache (RBAudioscrobblerUser *user, const char *request_name, const char *data)
{
	char *filename;
	char *file_uri;
	GError *error;

	filename = calculate_cached_response_path (user, request_name);
	file_uri = g_filename_to_uri (filename, NULL, NULL);

	error = NULL;
	if (rb_uri_create_parent_dirs (file_uri, &error)) {
		g_file_set_contents (filename, data, -1, &error);
	}

	if (error == NULL) {
		rb_debug ("saved %s to cache", request_name);
	} else {
		rb_debug ("error saving %s to cache: %s", request_name, error->message);
		g_error_free (error);
	}

	g_free (filename);
	g_free (file_uri);
}
