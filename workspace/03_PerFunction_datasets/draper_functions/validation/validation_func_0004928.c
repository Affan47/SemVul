scenarios_delete_clicked_cb (G_GNUC_UNUSED GtkWidget *button,
			     ScenariosState *state)
{
	data_analysis_output_t  dao;
	GtkTreeSelection        *selection;
	GtkTreeIter             iter;
	GtkTreeModel            *model;
	gchar                   *value;
	gboolean                all_deleted;
	GnmScenario             *sc;
	GList                   *l;

	restore_old_values (state);

	selection = gtk_tree_view_get_selection
	        (GTK_TREE_VIEW (state->scenarios_treeview));
	dao_init_new_sheet (&dao);
	dao.sheet = state->base.sheet;
	if (!gtk_tree_selection_get_selected (selection, NULL, &iter))
		return;
	model = gtk_tree_view_get_model
	        (GTK_TREE_VIEW (state->scenarios_treeview));

	gtk_tree_model_get (GTK_TREE_MODEL (model), &iter, 0, &value, -1);

	gtk_list_store_remove (GTK_LIST_STORE (model), &iter);

	sc = gnm_sheet_scenario_find (state->base.sheet, value);
	if (sc)
		g_object_set_data (G_OBJECT (sc),
				   "marked_deleted", GUINT_TO_POINTER (TRUE));

	set_selection_state (state, FALSE);

	all_deleted = TRUE;
	for (l = state->base.sheet->scenarios; l && all_deleted; l = l->next) {
		GnmScenario *sc = l->data;
		if (!g_object_get_data (G_OBJECT (sc), "marked_deleted"))
			all_deleted = FALSE;
	}

	gtk_widget_set_sensitive
		(state->summary_button, !all_deleted);
}
