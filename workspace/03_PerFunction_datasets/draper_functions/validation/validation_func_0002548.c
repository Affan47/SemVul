CbSetCurrent(void *data, unsigned current)
{
	PlaylistWindow *playlist_window = (PlaylistWindow *)data;
	if (current == 0)
	    return;

	GDK_THREADS_ENTER();

	GtkListStore *list = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(playlist_window->GetList())));
	GtkTreeIter iter;

	if (!current_play_pix) {
		current_play_pix = gdk_pixbuf_new_from_xpm_data((const char **)current_play_xpm);
		current_stop_pix = gdk_pixbuf_new_from_xpm_data((const char **)current_stop_xpm);

	} else {
		if (playlist_window->current_entry <= playlist_window->GetPlaylist()->Length()) {
			gchar *current_string = g_strdup_printf("%d", playlist_window->current_entry - 1);
			gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL(list), &iter, current_string);
			gtk_list_store_set (list, &iter, 0, NULL, -1);
			g_free(current_string);
		}
	}
	playlist_window->current_entry = current;

	gchar *current_string = g_strdup_printf("%d", playlist_window->current_entry - 1);
	gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL(list), &iter, current_string);

	if (playlist_window->GetPlaylist()->GetCorePlayer()->IsPlaying())
		gtk_list_store_set (list, &iter, 0, current_play_pix, -1);
	else
		gtk_list_store_set (list, &iter, 0, current_stop_pix, -1);

	g_free(current_string);
	GDK_THREADS_LEAVE();
}
