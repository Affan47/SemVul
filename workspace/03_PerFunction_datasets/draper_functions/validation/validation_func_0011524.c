replace_all_cb(GtkButton *button, gpointer unused)
{
	gchar *find_str = NULL, *rep_str = NULL, *flash;
	guint find_len, rep_len, offset, count, cursor_pos;
	GtkHex *gh;
	HexDocument *doc;
	GHexWindow *win = ghex_window_get_active();

	if(win == NULL || win->gh == NULL) {
		display_error_dialog (win, _("There is no active document to replace data in!"));
		return;
	}

	gh = win->gh;

	doc = gh->document;

	if((find_len = get_search_string(replace_dialog->f_doc, &find_str)) == 0) {
		display_error_dialog (win, _("There is no string to search for!"));
		return;
	}
	rep_len = get_search_string(replace_dialog->r_doc, &rep_str);

	if(find_len > doc->file_size - gh->cursor_pos)
		goto clean_up;

	count = 0;
	cursor_pos = 0;

	while(hex_document_find_forward(doc, cursor_pos, find_str, find_len,
									&offset)) {
		hex_document_set_data(doc, offset, rep_len, find_len, rep_str, TRUE);
		cursor_pos = offset + rep_len;
		count++;
	}

	gtk_hex_set_cursor(gh, MIN(offset, doc->file_size));

	if(count == 0) {
		display_info_dialog(win, _("No occurrences were found."));
	}

	flash = g_strdup_printf(ngettext("Replaced %d occurrence.",
									 "Replaced %d occurrences.",
									 count), count);
	ghex_window_flash(win, flash);
	g_free(flash);

 clean_up:
	if(NULL != find_str)
		g_free(find_str);
	if(NULL != rep_str)
		g_free(rep_str);
}
