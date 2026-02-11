giggle_diff_view_init (GiggleDiffView *diff_view)
{
	GiggleDiffViewPriv        *priv;
	PangoFontDescription      *font_desc;
	GtkTextBuffer             *buffer;
	GtkSourceLanguage         *language;
	GtkSourceLanguageManager  *manager;
	GtkTextIter                iter;

	priv = GET_PRIV (diff_view);

	priv->git = giggle_git_get ();

	priv->files = g_array_new (FALSE, TRUE, sizeof (GiggleDiffViewFile));
	priv->hunks = g_array_new (FALSE, TRUE, sizeof (GiggleDiffViewHunk));
	priv->current_hunk = -1;
	priv->current_style = STYLE_CHUNK;

	gtk_text_view_set_editable (GTK_TEXT_VIEW (diff_view), FALSE);
	gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (diff_view), FALSE);

	font_desc = pango_font_description_from_string ("monospace");
	gtk_widget_override_font (GTK_WIDGET (diff_view), font_desc);
	pango_font_description_free (font_desc);

	manager = gtk_source_language_manager_new ();
	language = gtk_source_language_manager_get_language (manager, "diff");

	if (language) {
		buffer = GTK_TEXT_BUFFER (gtk_source_buffer_new_with_language (language));
		gtk_source_buffer_set_highlight_syntax (GTK_SOURCE_BUFFER (buffer), TRUE);
		gtk_text_view_set_buffer (GTK_TEXT_VIEW (diff_view), buffer);

		gtk_text_buffer_get_start_iter (buffer, &iter);
		priv->search_mark = gtk_text_buffer_create_mark (buffer,
								 "search-mark",
								 &iter, FALSE);

		priv->invalid_char = gtk_text_buffer_create_tag (buffer, NULL, NULL);

		g_object_unref (buffer);
	}

	g_object_unref (manager);

}
