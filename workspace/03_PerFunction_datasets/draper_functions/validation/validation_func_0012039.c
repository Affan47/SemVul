cb_gimmix_playlist_save_response (GtkDialog *dlg, gint arg1, gpointer dialog)
{
	if (arg1 == GTK_RESPONSE_ACCEPT)
	{
		if (loaded_playlist != NULL)
		{
			mpd_database_delete_playlist (gmo, loaded_playlist);
			if ((mpd_database_save_playlist (gmo, loaded_playlist)) == MPD_DATABASE_PLAYLIST_EXIST)
				g_print (_("playlist already exists.\n"));
		}
		else
		{
			GList *widget_list;
			const gchar *text;

			widget_list = gtk_container_get_children (GTK_CONTAINER(GTK_DIALOG(dialog)->vbox));
			widget_list = widget_list->next;
			text = gtk_entry_get_text (GTK_ENTRY(widget_list->data));
			if ((mpd_database_save_playlist (gmo, (char*)text)) == MPD_DATABASE_PLAYLIST_EXIST)
				g_print (_("playlist already exists.\n"));

			g_list_free (widget_list);
			gimmix_load_playlist ((char*)text);
		}
		gimmix_update_playlists_treeview ();
	}

	gtk_widget_destroy (GTK_WIDGET(dlg));

	return;
}
