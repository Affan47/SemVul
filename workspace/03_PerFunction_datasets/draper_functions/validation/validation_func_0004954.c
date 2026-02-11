e2_filelist_clear_old_stores (gpointer user_data)
{
	GSList *tmp;
#ifdef DEBUG_MESSAGES
	gint debug = g_slist_length (app.used_stores);
#endif
	for (tmp = app.used_stores; tmp != NULL; tmp = tmp->next)
	{
		GtkListStore *store = tmp->data;
		GtkTreeModel *mdl = GTK_TREE_MODEL (store);
		GtkTreeIter iter;
		if (gtk_tree_model_get_iter_first (mdl, &iter))
		{


			FileInfo *info;
			do
			{
				gtk_tree_model_get (mdl, &iter, FINFO, &info, -1);
#ifdef USE_GLIB2_10
				g_slice_free1 (sizeof(FileInfo), info);

#else
				DEALLOCATE (FileInfo, info);
#endif
			} while (gtk_tree_model_iter_next (mdl, &iter));
		}

		g_object_unref (G_OBJECT (store));
	}
	g_slist_free (app.used_stores);
	app.used_stores = NULL;
	printd (DEBUG, "%d old liststore(s) cleared", debug);
	return FALSE;
}
