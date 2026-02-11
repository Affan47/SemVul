update_offset_fmt_from_entry(GtkEntry *entry, PropertyUI *pui)
{
	int i, len;
	gchar *old_offset_fmt;
	gboolean expect_spec;
	const GList *win_list;

	old_offset_fmt = offset_fmt;
	offset_fmt = g_strdup(gtk_entry_get_text(GTK_ENTRY(pui->format)));

	len = strlen(offset_fmt);
	expect_spec = FALSE;
	for(i = 0; i < len; i++) {
		if(offset_fmt[i] == '%')
			expect_spec = TRUE;
		if( expect_spec &&
			( (offset_fmt[i] >= 'a' && offset_fmt[i] <= 'z') ||
			  (offset_fmt[i] >= 'A' && offset_fmt[i] <= 'Z') ) ) {
			expect_spec = FALSE;
			if(offset_fmt[i] != 'x' && offset_fmt[i] != 'd' &&
			   offset_fmt[i] != 'o' && offset_fmt[i] != 'X' &&
			   offset_fmt[i] != 'P' && offset_fmt[i] != 'p') {
				GtkWidget *msg_dialog;

				g_free(offset_fmt);
				offset_fmt = old_offset_fmt;
				gtk_entry_set_text(GTK_ENTRY(pui->format), old_offset_fmt);
				msg_dialog =
					gtk_message_dialog_new(GTK_WINDOW(pui->pbox),
										   GTK_DIALOG_MODAL|
										   GTK_DIALOG_DESTROY_WITH_PARENT,
										   GTK_MESSAGE_ERROR,
										   GTK_BUTTONS_OK,
										   _("The offset format string contains invalid format specifier.\n"
											 "Only 'x', 'X', 'p', 'P', 'd' and 'o' are allowed."));
				gtk_dialog_run(GTK_DIALOG(msg_dialog));
				gtk_widget_destroy(msg_dialog);
				gtk_widget_grab_focus(pui->format);
				break;
			}
		}
	}
	if(offset_fmt != old_offset_fmt)
		g_free(old_offset_fmt);
	g_settings_set_string (settings,
	                       GHEX_PREF_OFFSET_FORMAT,
	                       offset_fmt);
	win_list = ghex_window_get_list();
	while(NULL != win_list) {
		ghex_window_update_status_message((GHexWindow *)win_list->data);
		win_list = win_list->next;
	}
}
