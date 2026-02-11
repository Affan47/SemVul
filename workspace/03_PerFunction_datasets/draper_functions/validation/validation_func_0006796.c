vte_send_selection_to_vte(void)
{
	GeanyDocument *doc;
	gchar *text;
	gsize len;

	doc = document_get_current();
	g_return_if_fail(doc != NULL);

	if (sci_has_selection(doc->editor->sci))
	{
		text = g_malloc0(sci_get_selected_text_length(doc->editor->sci) + 1);
		sci_get_selected_text(doc->editor->sci, text);
	}
	else
	{
		gint line_num = sci_get_current_line(doc->editor->sci);
		text = sci_get_line(doc->editor->sci, line_num);
	}

	len = strlen(text);

	if (vc->send_selection_unsafe)
	{

		if (text[len-1] != '\n' && text[len-1] != '\r')
		{
			SETPTR(text, g_strconcat(text, "\n", NULL));
			len++;
		}
	}
	else
	{
		while (text[len-1] == '\n' || text[len-1] == '\r')
		{
			text[len-1] = '\0';
			len--;
		}
	}

	vf->vte_terminal_feed_child(VTE_TERMINAL(vc->vte), text, len);


	gtk_notebook_set_current_page(GTK_NOTEBOOK(msgwindow.notebook), MSG_VTE);
	gtk_widget_grab_focus(vc->vte);
	msgwin_show_hide(TRUE);

	g_free(text);
}
