hex_document_remove_view(HexDocument *doc, GtkWidget *view)
{
	if(g_list_index(doc->views, view) == -1)
		return;

	doc->views = g_list_remove(doc->views, view);

	g_object_unref(view);
}
