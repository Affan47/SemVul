find_prev_cb(GtkButton *button, FindDialog *dialog)
{
	GtkHex *gh;
	guint offset, str_len;
	gchar *str;
	GHexWindow *win = ghex_window_get_active();

	if(win == NULL || win->gh == NULL) {
		display_error_dialog (win, _("There is no active document to search!"));
		return;
	}

	gh = win->gh;

	if((str_len = get_search_string(find_dialog->f_doc, &str)) == 0) {
		display_error_dialog (win, _("There is no string to search for!"));
		return;
	}

	if (dialog->auto_highlight) gtk_hex_delete_autohighlight(gh, dialog->auto_highlight);
	dialog->auto_highlight = NULL;
	dialog->auto_highlight = gtk_hex_insert_autohighlight(gh, str, str_len, "red");
	if(hex_document_find_backward(gh->document,
								  gh->cursor_pos, str, str_len, &offset))
		gtk_hex_set_cursor(gh, offset);
	else {
		ghex_window_flash(win, _("Beginning Of File reached"));
		display_info_dialog(win, _("String was not found!\n"));
	}
	if(NULL != str)
		g_free(str);
}
