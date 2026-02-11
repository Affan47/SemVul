gimmix_update_current_playlist (MpdObj *mo, MpdData *pdata)
{
	GtkListStore	*current_playlist_store;
	GtkTreeIter	current_playlist_iter;
	gint 		new;
	gint		current_song_id = -1;
	MpdData		*data = pdata;

	if (data!=NULL && mpd_check_connected(mo))
	{
		new = mpd_playlist_get_playlist_id (mo);
		current_song_id = mpd_player_get_current_song_id (mo);
	}
	else
	{
		return;
	}
	current_playlist_store = GTK_LIST_STORE (gtk_tree_view_get_model (GTK_TREE_VIEW(current_playlist_treeview)));
	gtk_list_store_clear (current_playlist_store);

	while (data != NULL)
	{
		gchar 	*title = NULL;
		gchar	*artist = NULL;
		gchar	*album = NULL;
		gchar 	*ti;
		gchar	time[15];

		if (data->song->id == current_song_id)
		{
			if (data->song->title != NULL)
			{


				title = g_markup_printf_escaped ("<span size=\"medium\"weight=\"bold\">%s</span>", data->song->title);
			}
			else
			{
				gchar *file = g_path_get_basename (data->song->file);
				gimmix_strip_file_ext (file);
				title = g_markup_printf_escaped ("<span size=\"medium\"weight=\"bold\">%s</span>", file);
				g_free (file);
			}
			if (data->song->artist != NULL)
			{
				artist = g_markup_printf_escaped ("<span size=\"medium\"weight=\"bold\">%s</span>", data->song->artist);
			}
			if (data->song->album != NULL)
			{
				album = g_markup_printf_escaped ("<span size=\"medium\"weight=\"bold\">%s</span>", data->song->album);
			}
			gimmix_get_total_time_for_song (mo, data->song, time);
			ti = g_markup_printf_escaped ("<span size=\"medium\" weight=\"bold\">%s</span>", time);
		}
		else
		{
			if (data->song->title != NULL)
			{


				title = g_markup_printf_escaped ("%s", data->song->title);
			}
			else
			{
				title = g_markup_printf_escaped ("%s", g_path_get_basename(data->song->file));
				gimmix_strip_file_ext (title);
			}
			if (data->song->artist)
			{
				artist = g_markup_printf_escaped ("%s", data->song->artist);
			}
			if (data->song->album)
			{
				album = g_markup_printf_escaped ("%s", data->song->album);
			}
			gimmix_get_total_time_for_song (mo, data->song, time);
			ti = NULL;
		}

		gtk_list_store_append (current_playlist_store, &current_playlist_iter);
		gtk_list_store_set (current_playlist_store,
							&current_playlist_iter,
							0, title,
							5, (ti!=NULL) ? ti : time,
							1, data->song->file,
							2, data->song->id,
							3, artist,
							4, album,
							-1);
		data = mpd_data_get_next (data);
		if (ti)
		g_free (ti);
		g_free (title);
		g_free (album);
		g_free (artist);
	}
	gtk_tree_view_set_model (GTK_TREE_VIEW (current_playlist_treeview), GTK_TREE_MODEL(current_playlist_store));
	gimmix_display_total_playlist_time (mo);


	return;
}
