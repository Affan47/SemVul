et_picture_save_file_data (const Picture *pic, GFile *file, GError **error)
{
    GFileOutputStream *file_ostream;
    gsize bytes_written;

    g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

    file_ostream = g_file_replace (file, NULL, FALSE, G_FILE_CREATE_NONE, NULL,
                                   error);

    if (!file_ostream)
    {
        g_assert (error == NULL || *error != NULL);
        return FALSE;
    }

    if (!g_output_stream_write_all (G_OUTPUT_STREAM (file_ostream), pic->data,
                                    pic->size, &bytes_written, NULL, error))
    {
        g_debug ("Only %" G_GSIZE_FORMAT " bytes out of %" G_GSIZE_FORMAT
                 " bytes of picture data were written", bytes_written,
                 pic->size);
        g_object_unref (file_ostream);
        g_assert (error == NULL || *error != NULL);
        return FALSE;
    }

    if (!g_output_stream_close (G_OUTPUT_STREAM (file_ostream), NULL, error))
    {
        g_object_unref (file_ostream);
        g_assert (error == NULL || *error != NULL);
        return FALSE;
    }

    g_assert (error == NULL || *error == NULL);
    g_object_unref (file_ostream);
    return TRUE;
}
