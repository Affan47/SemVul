click_find_cb (GtkWidget * widget,
               gpointer data)
{
	GSearchWindow * gsearch = data;
	gchar * command;

	if (gsearch->command_details->is_command_timeout_enabled == TRUE) {
		return;
	}

	if ((gsearch->command_details->command_status == STOPPED) ||
	    (gsearch->command_details->command_status == ABORTED)) {
	    	command = build_search_command (gsearch, TRUE);
		if (command != NULL) {
			spawn_search_command (gsearch, command);
			g_free (command);
		}
	}
}
