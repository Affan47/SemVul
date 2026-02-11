on_entry_config_force_ip_changed(GtkEditable *editable, gpointer unused_udata)
{
    gchar *text = STRTRACK(gtk_editable_get_chars(editable, 0, -1));
	const gchar *endptr;
	gboolean sensitive;

	(void) unused_udata;
	g_strstrip(text);
	sensitive = string_to_host_addr(text, &endptr, NULL) && '\0' == endptr[0];
	gtk_widget_set_sensitive(
        gui_dlg_prefs_lookup("checkbutton_config_force_ip"),
		sensitive);
	gtk_widget_set_sensitive(
        gui_dlg_prefs_lookup("checkbutton_config_bind_ipv4"),
		sensitive);
	G_FREE_NULL(text);
}
