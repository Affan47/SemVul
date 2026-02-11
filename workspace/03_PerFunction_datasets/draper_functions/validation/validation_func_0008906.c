evt_cmdseq_changed(GtkWidget *wid, gpointer user)
{
	P_Buttons	*page = user;
	Button		*btn;

	if((page != NULL) && ((btn = btn_button_get(page->button)) != NULL))
	{
		const gchar	*text;
		BtnFace		face;

		face = (BtnFace) GPOINTER_TO_UINT(g_object_get_data(G_OBJECT(wid), "face"));
		if((text = gtk_entry_get_text(GTK_ENTRY(wid))) != NULL)
		{
			btn_button_set_cmdseq(btn, face, text);
			page->modified = TRUE;
		}
	}
}
