build_gio_info(const DirPane *dp, const DirRow2 *row)
{
	GtkListStore		*lm = NULL;
	GtkWidget		*view, *scwin;
	GtkCellRenderer		*cr;
	GtkTreeViewColumn	*vc;
	GFile			*file;
	GFileInfo		*info;
	const gchar		*namespaces[] = { "standard", "access", "mountable", "unix", "time", "owner", "filesystem", NULL };
	gchar			**atts;
	guint			i, j;

	if((file = dp_get_file_from_row(dp, row)) == NULL)
		return NULL;
	info = g_file_query_info(file, "*", G_FILE_QUERY_INFO_NOFOLLOW_SYMLINKS, NULL, NULL);
	g_object_unref(file);
	if(info == NULL)
		return NULL;

	lm = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
	for(i = 0; namespaces[i] != NULL; i++)
	{
		atts = g_file_info_list_attributes(info, namespaces[i]);
		if(atts != NULL)
		{
			GtkTreeIter	iter;

			for(j = 0; atts[j] != NULL; j++)
			{
				gchar	*value;

				if((value = g_file_info_get_attribute_as_string(info, atts[j])) != NULL)
				{
					gtk_list_store_append(lm, &iter);
					gtk_list_store_set(lm, &iter, 0, atts[j], 1, value, -1);
					g_free(value);
				}
			}
			g_free(atts);
		}
	}

	view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(lm));
	cr = gtk_cell_renderer_text_new();
	vc = gtk_tree_view_column_new_with_attributes(_("Name"), cr, "text", 0, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), vc);
	vc = gtk_tree_view_column_new_with_attributes(_("Value"), cr, "text", 1, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), vc);

	scwin = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scwin), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(scwin), view);

	return scwin;
}
