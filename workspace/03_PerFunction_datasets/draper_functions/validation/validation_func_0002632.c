finish_search (GeditViewFrame    *frame,
	       gboolean           found)
{
	const gchar *entry_text = gtk_entry_get_text (GTK_ENTRY (frame->priv->search_entry));

	if (found || (entry_text[0] == '\0'))
	{
		gedit_view_scroll_to_cursor (frame->priv->view);

		set_search_state (frame, SEARCH_STATE_NORMAL);
	}
	else
	{
		set_search_state (frame, SEARCH_STATE_NOT_FOUND);
	}
}
