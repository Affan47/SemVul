on_execute_until(GtkButton *button, gpointer user_data)
{
	GeanyDocument *doc = document_get_current();
	if (doc)
	{
		int line = sci_get_current_line(doc->editor->sci) + 1;
		debug_execute_until(DOC_FILENAME(doc), line);
	}
}
