ipod_dirs_present(const gchar *mountpoint) {
    gchar *file;
    gchar *dir;
    gboolean result = TRUE;

    g_return_val_if_fail (mountpoint, FALSE);

    dir = itdb_get_music_dir(mountpoint);
    if (!dir)
        return FALSE;

    file = itdb_get_path(dir, "F00");
    if (!file || !g_file_test(file, G_FILE_TEST_IS_DIR))
        result = FALSE;
    g_free(file);
    g_free(dir);

    dir = itdb_get_itunes_dir(mountpoint);
    if (!dir || !g_file_test(dir, G_FILE_TEST_IS_DIR))
        result = FALSE;
    g_free(dir);

    return result;
}
