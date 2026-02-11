sobs_to_list(GtkWidget *list, GList *sol)
{
	GList *sl;
	struct star_obs *sob;
	GtkTreeModel *store;
	GtkTreeIter iter;

	store = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

	sl = sol;
	while (sl != NULL) {
		sob = STAR_OBS(sl->data);
		sl = g_list_next(sl);

		gtk_list_store_append(GTK_LIST_STORE(store), &iter);
		sob_store_set_row_vals(GTK_LIST_STORE(store), &iter, sob);
	}
}
