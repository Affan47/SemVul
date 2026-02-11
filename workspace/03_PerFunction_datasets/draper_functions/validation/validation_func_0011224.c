vflist_listview_add_column(ViewFile *vf, gint n, const gchar *title, gboolean image, gboolean right_justify, gboolean expand)
{
	GtkTreeViewColumn *column;
	GtkCellRenderer *renderer;

	column = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(column, title);
	gtk_tree_view_column_set_min_width(column, 4);

	if (!image)
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_GROW_ONLY);
		renderer = gtk_cell_renderer_text_new();
		if (right_justify)
			{
			g_object_set(G_OBJECT(renderer), "xalign", 1.0, NULL);
			}
		gtk_tree_view_column_pack_start(column, renderer, TRUE);
		gtk_tree_view_column_add_attribute(column, renderer, "text", n);
		if (expand)
			gtk_tree_view_column_set_expand(column, TRUE);
		}
	else
		{
		gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
		renderer = gtk_cell_renderer_pixbuf_new();
		cell_renderer_height_override(renderer);
		gtk_tree_view_column_pack_start(column, renderer, TRUE);
		gtk_tree_view_column_add_attribute(column, renderer, "pixbuf", n);
		}

	gtk_tree_view_column_set_cell_data_func(column, renderer, vflist_listview_color_cb, vf, NULL);
	g_object_set_data(G_OBJECT(column), "column_store_idx", GUINT_TO_POINTER(n));
	g_object_set_data(G_OBJECT(renderer), "column_store_idx", GUINT_TO_POINTER(n));

	gtk_tree_view_append_column(GTK_TREE_VIEW(vf->listview), column);
}
