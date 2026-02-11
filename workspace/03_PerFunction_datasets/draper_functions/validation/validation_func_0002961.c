album_info_new (void)
{
	AlbumInfo *album;

	album = g_new0 (AlbumInfo, 1);

	album->ref = 1;
	album->release_date = g_date_new ();
	album_info_set_id (album, NULL);
	album_info_set_title (album, NULL);
	album_info_set_artist (album, NULL, NULL);
	album_info_set_tracks (album, NULL);

	return album;
}
