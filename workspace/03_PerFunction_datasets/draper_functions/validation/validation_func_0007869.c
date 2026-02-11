prefs_actions_down(GtkWidget *w, gpointer data)
{
	GtkListStore *store = NULL;
	GtkTreeModel *model = NULL;
	GtkTreeIter next, sel;
	GtkTreePath *try;

	if (!gtk_tree_selection_get_selected
		(gtk_tree_view_get_selection
			(GTK_TREE_VIEW(actions.actions_list_view)),
		 &model,
		 &sel))
		return;
	store = (GtkListStore *)model;
	try = gtk_tree_model_get_path(GTK_TREE_MODEL(store), &sel);
	if (!try)
		return;


	if (!gtk_tree_path_prev(try)) {
		gtk_tree_path_free(try);
		return;
	}
	gtk_tree_path_free(try);

	next = sel;
	if (!gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &next))
		return;

	gtk_list_store_swap(store, &next, &sel);
	prefs_actions_set_list();
	modified_list = TRUE;
}
