gedit_window_get_unsaved_documents (GeditWindow *window)
{
	GList *res = NULL;

	g_return_val_if_fail (GEDIT_IS_WINDOW (window), NULL);

	gedit_multi_notebook_foreach_tab (window->priv->multi_notebook,
					  (GtkCallback)add_unsaved_doc,
					  &res);

	return g_list_reverse (res);
}
