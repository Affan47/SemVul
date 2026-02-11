xfade_update(void)
{
	if (mpd_status_get_crossfade(connection) > 0)
	{
		gtk_spin_button_set_value(GTK_SPIN_BUTTON(gtk_builder_get_object(server_pref_xml, "sb_fade_time")),
								  mpd_status_get_crossfade(connection));
	}
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(gtk_builder_get_object(server_pref_xml, "cb_fading")),
								 mpd_status_get_crossfade(connection) ? TRUE : FALSE);

	gtk_widget_set_sensitive(GTK_WIDGET(gtk_builder_get_object(server_pref_xml, "sb_fade_time")),
							 (mpd_status_get_crossfade(connection)) ? TRUE : FALSE);

}
