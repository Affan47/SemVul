pl3_file_browser_destroy(void)
{
	if (pl3_fb_tree_ref)
	{
		GtkTreeIter iter;
		GtkTreePath *path;
		path = gtk_tree_row_reference_get_path(pl3_fb_tree_ref);
		if (path)
		{
			if (gtk_tree_model_get_iter(GTK_TREE_MODEL(gtk_tree_row_reference_get_model(pl3_fb_tree_ref)), &iter, path))
			{
				gtk_list_store_remove(GTK_LIST_STORE(gtk_tree_row_reference_get_model(pl3_fb_tree_ref)), &iter);
			}
			gtk_tree_path_free(path);
		}
		gtk_tree_row_reference_free(pl3_fb_tree_ref);
		pl3_fb_tree_ref = NULL;
	}
	if (pl3_fb_vbox)
	{
		gtk_widget_destroy(pl3_fb_vbox);
        pl3_fb_vbox = NULL;
	}
	if (pl3_fb_store2)
	{
		g_object_unref(pl3_fb_store2);
        pl3_fb_store2 = NULL;
	}
    if(pl3_fb_tree) {
        pl3_fb_tree = NULL;
    }
}
