playlist_length_get (cli_infos_t *infos, const gchar *playlist, gint *len)
{
	xmmsv_coll_t *coll;

	if (playlist) {


		if ((coll = get_coll (infos, playlist, XMMS_COLLECTION_NS_PLAYLISTS))) {
			*len = xmmsv_coll_idlist_get_size (coll);
			xmmsv_coll_unref (coll);
		} else {
			return FALSE;
		}
	} else {
		*len = infos->cache->active_playlist->len;
	}

	return TRUE;
}
