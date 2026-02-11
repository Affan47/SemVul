prefs_get_cfgdir() {
    gchar *folder;


    folder = g_build_filename(g_get_home_dir(), ".gtkpod", NULL);

    if (!g_file_test(folder, G_FILE_TEST_IS_DIR)) {
        if ((g_mkdir(folder, 0777)) == -1) {
            printf(_("Couldn't create '%s'\n"), folder);
            g_free(folder);
            return NULL;
        }
    }
    return folder;
}
