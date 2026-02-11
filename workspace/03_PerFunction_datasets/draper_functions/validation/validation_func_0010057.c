xmms_playlist_client_insert_url (xmms_playlist_t *playlist, const gchar *plname,
                                 gint32 pos, const gchar *url, xmms_error_t *err)
{
	xmms_medialib_entry_t entry = 0;
	xmms_medialib_session_t *session = xmms_medialib_begin_write ();

	entry = xmms_medialib_entry_new_encoded (session, url, err);
	xmms_medialib_end (session);

	if (!entry) {
		return;
	}

	xmms_playlist_client_insert_id (playlist, plname, pos, entry, err);
}
