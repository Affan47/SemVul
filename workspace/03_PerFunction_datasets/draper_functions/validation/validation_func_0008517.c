_populateWindowData(void)
{
	GtkListStore *model;
	GtkTreeIter iter;

	model = gtk_list_store_new (2,
							    G_TYPE_STRING,
								G_TYPE_INT);

	for (UT_sint32 i = 0; i < _getDocumentCount(); i++)
    {
		const char *s = _getNthDocumentName(i);
		UT_return_if_fail(s);

		gtk_list_store_append (model, &iter);

		gtk_list_store_set (model, &iter,
							0, s,
							1, i,
							-1);
    }

	gtk_tree_view_set_model(GTK_TREE_VIEW(m_listWindows), reinterpret_cast<GtkTreeModel *>(model));

	g_object_unref (model);


 	gtk_widget_grab_focus (m_listWindows);
}
