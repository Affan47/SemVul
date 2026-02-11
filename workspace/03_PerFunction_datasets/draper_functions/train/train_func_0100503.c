gp_itdb_pc_path_hash_find_tracks(iTunesDB *itdb, const gchar *filename) {
    ExtraiTunesDBData *eitdb;
    GList *tracks = NULL;

    g_return_val_if_fail (itdb, NULL);
    eitdb = itdb->userdata;
    g_return_val_if_fail (eitdb, NULL);
    g_return_val_if_fail (eitdb->pc_path_hash, NULL);

    if (filename && *filename)
        tracks = g_hash_table_lookup(eitdb->pc_path_hash, filename);

    return g_list_copy(tracks);
}
