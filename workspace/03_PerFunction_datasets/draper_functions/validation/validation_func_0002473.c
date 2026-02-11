ario_playlist_filter_func (GtkTreeModel *model,
                           GtkTreeIter  *iter,
                           ArioPlaylist *playlist)
{
        ARIO_LOG_FUNCTION_START;
        gchar *title, *artist, *album, *genre;
        gboolean visible = TRUE, filter;
        int i;
        gchar **cmp_str;


        if (!playlist->priv->search_text || *playlist->priv->search_text == '\0')
                return TRUE;


        cmp_str = g_strsplit (playlist->priv->search_text, " ", -1);
        if (!cmp_str)
                return TRUE;


        gtk_tree_model_get (model, iter,
                            TITLE_COLUMN, &title,
                            ARTIST_COLUMN, &artist,
                            ALBUM_COLUMN, &album,
                            GENRE_COLUMN, &genre,
                            -1);


        for (i = 0; cmp_str[i] && visible; ++i) {
                if (g_utf8_collate (cmp_str[i], ""))
                {

                        filter = FALSE;


                        if (title
                            && ario_conf_get_boolean (PREF_TITLE_COLUMN_VISIBLE, PREF_TITLE_COLUMN_VISIBLE_DEFAULT)
                            && ario_util_stristr (title, cmp_str[i])) {
                                filter = TRUE;
                        } else if (artist
                                   && ario_conf_get_boolean (PREF_ARTIST_COLUMN_VISIBLE, PREF_ARTIST_COLUMN_VISIBLE_DEFAULT)
                                   && ario_util_stristr (artist, cmp_str[i])) {
                                filter = TRUE;
                        } else if (album
                                   && ario_conf_get_boolean (PREF_ALBUM_COLUMN_VISIBLE, PREF_ALBUM_COLUMN_VISIBLE_DEFAULT)
                                   && ario_util_stristr (album, cmp_str[i])) {
                                filter = TRUE;
                        } else if (genre
                                   && ario_conf_get_boolean (PREF_GENRE_COLUMN_VISIBLE, PREF_GENRE_COLUMN_VISIBLE_DEFAULT)
                                   && ario_util_stristr (genre, cmp_str[i])) {
                                filter = TRUE;
                        }


                        visible &= filter;
                }
        }

        g_strfreev (cmp_str);
        g_free (title);
        g_free (artist);
        g_free (album);
        g_free (genre);

        return visible;
}
