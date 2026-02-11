gm_mcp_icecrew_userlist_icon_path(GmMcpIcecrewUserlist *package,
		GmPlayerdbPlayerInfo *ppi, gboolean use_state) {
	gchar const *state;
	gchar const *icon_path = NULL;

	state = gm_playerdb_player_info_get_prop(ppi,
			package->priv->property_names[P_STATE]);

	if (!use_state || (state != NULL && strcmp(state, "avail") == 0)) {
		gm_mcp_icecrew_userlist_find_path(package->priv->rank_icons,
				gm_playerdb_player_info_get_prop(ppi,
						package->priv->property_names[P_RANK]), &icon_path);
	} else {
		gm_mcp_icecrew_userlist_find_path(package->priv->state_icons,
				state, &icon_path);

	}

	return icon_path;
}
