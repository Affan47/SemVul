ario_shell_coverselect_get_covers_cb (GtkWidget *widget,
                                      ArioShellCoverselect *shell_coverselect)
{
        ARIO_LOG_FUNCTION_START;
        const gchar *artist;
        const gchar *album;
        gboolean ret;


        ario_shell_coverselect_set_sensitive (shell_coverselect, FALSE);

        artist = gtk_entry_get_text (GTK_ENTRY (shell_coverselect->priv->artist_entry));
        album = gtk_entry_get_text (GTK_ENTRY (shell_coverselect->priv->album_entry));


        if (shell_coverselect->priv->file_size)
                g_array_free (shell_coverselect->priv->file_size, TRUE);
        g_slist_foreach (shell_coverselect->priv->file_contents, (GFunc) g_free, NULL);
        g_slist_free (shell_coverselect->priv->file_contents);
        shell_coverselect->priv->file_contents = NULL;


        shell_coverselect->priv->file_size = g_array_new (TRUE, TRUE, sizeof (int));

        ret = ario_cover_manager_get_covers (ario_cover_manager_get_instance (),
                                             artist,
                                             album,
                                             shell_coverselect->priv->path,
                                             &shell_coverselect->priv->file_size,
                                             &shell_coverselect->priv->file_contents,
                                             GET_ALL_COVERS);


        ario_shell_coverselect_show_covers (shell_coverselect);


        ario_shell_coverselect_set_sensitive (shell_coverselect, TRUE);
}
