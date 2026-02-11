toggle_sensitivity(GtkWidget *w, gint pos1, gint pos2, gint *pos3)
{
	if (pos3) {
		if (!entry_len)
			gtk_dialog_set_response_sensitive(GTK_DIALOG(gtk_widget_get_toplevel(w)),
				GTK_RESPONSE_OK, TRUE);
		entry_len += pos2;

	} else {
		entry_len = entry_len + pos1 - pos2;
		if (!entry_len)
			gtk_dialog_set_response_sensitive(GTK_DIALOG(gtk_widget_get_toplevel(w)),
				GTK_RESPONSE_OK, FALSE);
	}
}
