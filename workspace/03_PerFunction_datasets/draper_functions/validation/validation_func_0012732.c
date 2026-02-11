fe_clear_channel (session *sess)
{
	char tbuf[CHANLEN+6];
	session_gui *gui = sess->gui;

	if (sess->gui->is_tab)
	{
		if (sess->waitchannel[0])
		{
			if (prefs.hex_gui_tab_trunc > 2 && g_utf8_strlen (sess->waitchannel, -1) > prefs.hex_gui_tab_trunc)
			{

				tbuf[0] = '(';
				strcpy (tbuf + 1, sess->waitchannel);
				g_utf8_offset_to_pointer(tbuf, prefs.hex_gui_tab_trunc)[0] = 0;
				strcat (tbuf, "..)");
			} else
			{
				sprintf (tbuf, "(%s)", sess->waitchannel);
			}
		}
		else
			strcpy (tbuf, _("<none>"));
		chan_rename (sess->res->tab, tbuf, prefs.hex_gui_tab_trunc);
	}

	if (!sess->gui->is_tab || sess == current_tab)
	{
		gtk_entry_set_text (GTK_ENTRY (gui->topic_entry), "");

		if (gui->op_xpm)
		{
			gtk_widget_destroy (gui->op_xpm);
			gui->op_xpm = 0;
		}
	} else
	{
		if (sess->res->topic_text)
		{
			free (sess->res->topic_text);
			sess->res->topic_text = NULL;
		}
	}
}
