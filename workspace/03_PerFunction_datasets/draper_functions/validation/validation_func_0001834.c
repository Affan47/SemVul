each_path_get_data_binder (NemoDragEachSelectedItemDataGet data_get,
			   gpointer context,
			   gpointer data)
{
	DragDataGetInfo *info;
	GList *l;
	NemoFile *file;
	GtkTreeRowReference *row;
	GtkTreePath *path;
	char *uri;
	GdkRectangle cell_area;
	GtkTreeViewColumn *column;

	info = context;

	g_return_if_fail (info->model->details->drag_view);

	column = gtk_tree_view_get_column (info->model->details->drag_view, 0);

	for (l = info->path_list; l != NULL; l = l->next) {
		row = l->data;

		path = gtk_tree_row_reference_get_path (row);
		file = nemo_list_model_file_for_path (info->model, path);
		if (file) {
			gtk_tree_view_get_cell_area
				(info->model->details->drag_view,
				 path,
				 column,
				 &cell_area);

			uri = nemo_file_get_uri (file);

			(*data_get) (uri,
				     0,
				     cell_area.y - info->model->details->drag_begin_y,
				     cell_area.width, cell_area.height,
				     data);

			g_free (uri);

			nemo_file_unref (file);
		}

		gtk_tree_path_free (path);
	}
}
