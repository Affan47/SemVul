video_thumbnail_setup_cache() {
    gchar *cachedir = NULL;
    gchar *cfgdir = prefs_get_cfgdir();

    if (!cfgdir)
        return NULL;

    cachedir = g_build_filename(cfgdir, "video_thumbnail_cache", NULL);
    g_free(cfgdir);

    if (!g_file_test(cachedir, G_FILE_TEST_IS_DIR) && (g_mkdir(cachedir, 0777) == -1)) {
        gtkpod_warning(_("Could not create '%s'"), cachedir);
        g_free(cachedir);
        cachedir = NULL;
    }

    return cachedir;
}
