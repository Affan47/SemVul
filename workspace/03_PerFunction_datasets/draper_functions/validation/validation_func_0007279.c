on_action_edit_paste(GtkAction *action, GmAppView *view) {
	GtkWidget *active = gtk_window_get_focus(GTK_WINDOW(view));
	GtkClipboard *clip = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	GtkTextBuffer *buf;

	if (active && GTK_IS_TEXT_VIEW(active)) {
		buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(active));
		gtk_text_buffer_paste_clipboard(buf, clip, NULL, TRUE);
	}
}
