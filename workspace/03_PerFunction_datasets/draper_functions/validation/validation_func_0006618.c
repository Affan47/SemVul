evt_id_entry_changed(GtkWidget *wid, gpointer user)
{
	P_Types		*page = user;
	const gchar	*text;
	gint		index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(wid), "user"));

	if(page->curr_type == NULL)
		return TRUE;

	page->modified = TRUE;

	text = gtk_entry_get_text(GTK_ENTRY(wid));


	switch(index)
	{
		case 0:
			g_strlcpy(page->curr_type->suffix, text, sizeof page->curr_type->suffix);
			break;
		case 1:
			g_strlcpy(page->curr_type->name_re_src, text, sizeof page->curr_type->name_re_src);
			break;
		case 2:
			g_strlcpy(page->curr_type->file_re_src, text, sizeof page->curr_type->file_re_src);
			break;
	}
	return TRUE;
}
