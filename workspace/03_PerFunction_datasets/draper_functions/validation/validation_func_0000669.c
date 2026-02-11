mark_tooltip_func (GtkSourceMarkAttributes *attrs,
                   GtkSourceMark           *mark,
                   GtkSourceView           *view)
{
	GtkTextBuffer *buffer;
	GtkTextIter iter;
	gint line;
	gint column;

	buffer = gtk_text_mark_get_buffer (GTK_TEXT_MARK (mark));

	gtk_text_buffer_get_iter_at_mark (buffer, &iter, GTK_TEXT_MARK (mark));
	line = gtk_text_iter_get_line (&iter) + 1;
	column = gtk_text_iter_get_line_offset (&iter);

	if (g_strcmp0 (gtk_source_mark_get_category (mark), MARK_TYPE_1) == 0)
	{
		return g_strdup_printf ("Line: %d, Column: %d", line, column);
	}
	else
	{
		return g_strdup_printf ("<b>Line</b>: %d\n<i>Column</i>: %d", line, column);
	}
}
