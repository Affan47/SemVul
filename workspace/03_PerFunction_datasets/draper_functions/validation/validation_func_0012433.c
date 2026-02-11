connect_to_mpd(void)
{
	char *string = NULL;
	if (connecting_lock == NULL)
	{
		connecting_lock = g_mutex_new();
	}
	if (!  g_mutex_trylock(connecting_lock))
	{
		return FALSE;
	}


	string = connection_get_hostname();
	mpd_set_hostname(connection, string);


	mpd_set_port(connection, connection_get_port());


	mpd_set_connection_timeout(connection,
							   cfg_get_single_value_as_float_with_default(config, "connection", "timeout",
																		  DEFAULT_TIMEOUT));

	if (connection_use_auth())
	{
		string = connection_get_password();
		mpd_set_password(connection, string);
	} else
	{
		mpd_set_password(connection, "");
	}
	g_thread_create((GThreadFunc) connection_thread, NULL, FALSE, NULL);
	connecting_pulse = g_timeout_add(200, (GSourceFunc) (connecting_pulse_callback), NULL);
	gtk_progress_bar_set_text(GTK_PROGRESS_BAR(gtk_builder_get_object(pl3_xml, "pl3_progressbar")), _("Connecting"));
	gtk_widget_show(GTK_WIDGET(gtk_builder_get_object(pl3_xml, "pl3_progressbar")));


	gmpc_connected = TRUE;

	return FALSE;
}
