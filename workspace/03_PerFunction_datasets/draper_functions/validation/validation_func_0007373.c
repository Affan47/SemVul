is_tle_file (const gchar *dir, const gchar *fnam)
{
    gchar    *path;
    gchar    *fname_lower;
    gboolean  fileIsOk = FALSE;

    path = g_strconcat (dir, G_DIR_SEPARATOR_S, fnam, NULL);
    fname_lower=g_ascii_strdown(fnam,-1);

    if (g_file_test (path, G_FILE_TEST_IS_REGULAR) &&
        (g_str_has_suffix(fname_lower, ".tle") || g_str_has_suffix(fname_lower, ".txt")))
    {
        fileIsOk = TRUE;
    }
    g_free (fname_lower);
    g_free (path);

    return fileIsOk;
}
