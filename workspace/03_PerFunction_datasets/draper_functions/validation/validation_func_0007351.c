nemo_list_view_finalize (GObject *object)
{
	NemoListView *list_view;

	list_view = NEMO_LIST_VIEW (object);

	g_free (list_view->details->original_name);
	list_view->details->original_name = NULL;

	if (list_view->details->double_click_path[0]) {
		gtk_tree_path_free (list_view->details->double_click_path[0]);
	}
	if (list_view->details->double_click_path[1]) {
		gtk_tree_path_free (list_view->details->double_click_path[1]);
	}
	if (list_view->details->new_selection_path) {
		gtk_tree_path_free (list_view->details->new_selection_path);
	}

	g_list_free (list_view->details->cells);
	g_hash_table_destroy (list_view->details->columns);

	if (list_view->details->hover_path != NULL) {
		gtk_tree_path_free (list_view->details->hover_path);
	}

	if (list_view->details->column_editor != NULL) {
		gtk_widget_destroy (list_view->details->column_editor);
	}

	g_free (list_view->details);

	g_signal_handlers_disconnect_by_func (nemo_preferences,
					      default_sort_order_changed_callback,
					      list_view);
	g_signal_handlers_disconnect_by_func (nemo_list_view_preferences,
					      default_zoom_level_changed_callback,
					      list_view);
	g_signal_handlers_disconnect_by_func (nemo_list_view_preferences,
					      default_visible_columns_changed_callback,
					      list_view);
	g_signal_handlers_disconnect_by_func (nemo_list_view_preferences,
					      default_column_order_changed_callback,
					      list_view);

	G_OBJECT_CLASS (nemo_list_view_parent_class)->finalize (object);
}
