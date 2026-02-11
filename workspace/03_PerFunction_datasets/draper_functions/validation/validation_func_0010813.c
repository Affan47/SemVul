get_entry_uri (const gchar *id)
{

	const gchar *video_id = NULL;
	gchar **parts, *uri;
	guint i;

	parts = g_strsplit (id, ":", -1);

	for (i = 0; parts[i] != NULL && parts[i + 1] != NULL; i += 2) {
		if (strcmp (parts[i], "video") == 0) {
			video_id = parts[i + 1];
			break;
		}
	}

	g_assert (video_id != NULL);


	uri = g_strconcat ("https://gdata.youtube.com/feeds/api/videos/", video_id, NULL);
	g_strfreev (parts);

	return uri;
}
