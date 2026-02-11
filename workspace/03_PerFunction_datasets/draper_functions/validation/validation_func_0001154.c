gm_color_table_disconnect_font_changed(GmColorTable *table) {
	GConfClient *conf;

	if (table->priv->gconf_connection_id) {
		conf = gconf_client_get_default();
		gconf_client_notify_remove(conf, table->priv->gconf_connection_id);
		gconf_client_remove_dir(conf, MONOSPACE_FONT_DIR, NULL);
		table->priv->gconf_connection_id = 0;
		g_object_unref(G_OBJECT(conf));
	}
}
