get_playlist_prefs_key(gint index, Playlist *pl, const gchar *subkey) {
    g_return_val_if_fail (pl, NULL);
    g_return_val_if_fail (subkey, NULL);

    return g_strdup_printf("itdb_%d_playlist_%llu_%s", index, (unsigned long long) pl->id, subkey);
}
