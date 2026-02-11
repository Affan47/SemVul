ghwp_file_v3_new_from_uri (const gchar *uri, GError **error)
{
    g_return_val_if_fail (uri != NULL, NULL);

    gchar      *filename = g_filename_from_uri (uri, NULL, error);
    GHWPFileV3 *file     = ghwp_file_v3_new_from_filename (filename, error);
    g_free (filename);
    return file;
}
