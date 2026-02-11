gtk_hex_delete_autohighlight(GtkHex *gh, GtkHex_AutoHighlight *ahl)
{
	g_free(ahl->search_string);
	g_free(ahl->colour);

	while (ahl->highlights)
	{
		gtk_hex_delete_highlight(gh, ahl, ahl->highlights);
	}

	if (ahl->next) ahl->next->prev = ahl->prev;
	if (ahl->prev) ahl->prev->next = ahl->next;

	if (gh->auto_highlight == ahl) gh->auto_highlight = ahl->next;

	g_free(ahl);
}
