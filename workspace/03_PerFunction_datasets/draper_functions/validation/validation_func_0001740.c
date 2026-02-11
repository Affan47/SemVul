album_tabulator (gpointer id, DMAPRecord * record, GHashTable * ht)
{
	const gchar *album;

	g_object_get (record, "songalbum", &album, NULL);
	if (!album)
		return;
	if (!g_hash_table_lookup (ht, album))
		g_hash_table_insert (ht, (gchar *) album, NULL);
}
