ario_util_get_dnd_pixbuf_from_albums (const GSList *albums)
{
        ARIO_LOG_FUNCTION_START;
        const GSList *tmp;
        GSList *covers = NULL;
        gchar *cover_path;
        ArioServerAlbum *ario_server_album;
        int len = 0;
        GdkPixbuf *pixbuf;

        if (!albums)
                return NULL;


        for (tmp = albums; tmp && len < MAX_COVERS_IN_DRAG; tmp = g_slist_next (tmp)) {
                ario_server_album = tmp->data;

                cover_path = ario_cover_make_cover_path (ario_server_album->artist, ario_server_album->album, SMALL_COVER);
                if (ario_util_uri_exists (cover_path)) {
                        covers = g_slist_append (covers, cover_path);
                        ++len;
                } else {
                        g_free (cover_path);
                }
        }


        pixbuf = ario_util_get_dnd_pixbuf_from_cover_paths (covers);

        g_slist_foreach (covers, (GFunc) g_free, NULL);
        g_slist_free (covers);

        return pixbuf;
}
