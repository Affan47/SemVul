gfire_server_browser_add_configured_games_cb(const gfire_game_configuration *p_gconf,
															 GtkComboBox *p_game_combo)
{

	const gchar *protocol = gfire_game_server_query_type(p_gconf->game_id);
	if(protocol)
	{
		const gfire_game *game = gfire_game_by_id(p_gconf->game_id);
		if(game)
		{
			GtkListStore *store = GTK_LIST_STORE(gtk_combo_box_get_model(p_game_combo));
			GtkTreeIter iter;
			gtk_list_store_append(store, &iter);
			gtk_list_store_set(store, &iter, 0, game->name, 1, game->id, -1);
		}
	}

	return FALSE;
}
