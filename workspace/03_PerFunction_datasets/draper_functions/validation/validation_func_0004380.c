media_art_request_download (MediaArtType  type,
                            const gchar  *album,
                            const gchar  *artist,
                            const gchar  *local_uri,
                            const gchar  *art_path)
{
	if (connection) {
		FileInfo *info;

		if (disable_requests) {
			return;
		}

		if (type != MEDIA_ART_ALBUM) {
			return;
		}

		info = file_info_new (local_uri, art_path);

		g_dbus_connection_call (connection,
		                        ALBUMARTER_SERVICE,
		                        ALBUMARTER_PATH,
		                        ALBUMARTER_INTERFACE,
		                        "Queue",
		                        g_variant_new ("(sssu)",
		                                       artist ? artist : "",
		                                       album ? album : "",
		                                       "album",
		                                       0),
		                        NULL,
		                        G_DBUS_CALL_FLAGS_NONE,
		                        -1,
		                        NULL,
		                        media_art_queue_cb,
		                        info);
	}
}
