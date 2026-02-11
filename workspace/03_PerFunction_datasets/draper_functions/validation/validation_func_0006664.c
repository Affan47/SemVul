gwy_app_recent_file_list_load(const gchar *filename)
{
    GtkTreeIter iter;
    GError *err = NULL;
    gchar *buffer = NULL;
    gsize size = 0;
    gchar **files;
    guint n, nrecent;

    gwy_app_recent_file_create_dirs();

    g_return_val_if_fail(gcontrols.store == NULL, FALSE);
    gcontrols.store = gtk_list_store_new(1, G_TYPE_POINTER);

    if (!filename)
        return TRUE;

    if (!g_file_get_contents(filename, &buffer, &size, &err)) {
        g_clear_error(&err);
        return FALSE;
    }

#ifdef G_OS_WIN32
    gwy_strkill(buffer, "\r");
#endif
    files = g_strsplit(buffer, "\n", 0);
    g_free(buffer);
    if (!files)
        return TRUE;

    nrecent = _gwy_app_get_n_recent_files();
    for (n = 0; files[n]; n++) {
        if (*files[n]) {
            GwyRecentFile *rf;

            gwy_debug("%s", files[n]);
            rf = gwy_app_recent_file_new(gwy_canonicalize_path(files[n]), NULL);
            gtk_list_store_insert_with_values(gcontrols.store, &iter, G_MAXINT,
                                              FILELIST_RAW, rf,
                                              -1);
            if (n < nrecent) {
                gcontrols.recent_file_list
                    = g_list_append(gcontrols.recent_file_list, rf->file_utf8);
            }
        }
        g_free(files[n]);
    }
    g_free(files);

    return TRUE;
}
