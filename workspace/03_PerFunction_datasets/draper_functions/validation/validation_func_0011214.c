ario_shell_coverdownloader_get_cover_from_album (ArioShellCoverdownloader *ario_shell_coverdownloader,
                                                 const ArioServerAlbum *server_album,
                                                 const ArioShellCoverdownloaderOperation operation)
{
        ARIO_LOG_FUNCTION_START;
        const gchar *artist;
        const gchar *album;
        const gchar *path;
        ArioShellCoverdownloaderIdleData *data;

        if (!server_album)
                return;

        artist = server_album->artist;
        album = server_album->album;
        path = server_album->path;

        if (!album || !artist)
                return;

        switch (operation) {
        case GET_COVERS:

                data = (ArioShellCoverdownloaderIdleData *) g_malloc0 (sizeof (ArioShellCoverdownloaderIdleData));

                data->ario_shell_coverdownloader = ario_shell_coverdownloader;
                data->artist = g_strdup (artist);
                data->album = g_strdup (album);
                g_idle_add ((GSourceFunc) ario_shell_coverdownloader_progress_update, data);

                if (ario_cover_cover_exists (artist, album))

                        ++ario_shell_coverdownloader->priv->nb_covers_already_exist;
                else

                        ario_shell_coverdownloader_get_cover (ario_shell_coverdownloader, artist, album, path);
                break;

        case REMOVE_COVERS:

                ario_cover_remove_cover (artist, album);
                break;

        default:
                break;
        }
}
